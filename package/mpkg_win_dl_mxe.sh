#!/usr/bin/env bash

# Copyright 2017 Viktor Szakats
# License: The MIT license (MIT)

set -ue

usage() {
  echo "Download and unpack a list of MXE binary packages along with their
dependencies, securely.

Usage: $(basename "$0") [package ...]

Environment:

MXE_HOME          Configure directory where packages will be installed.
                  Default: ~/mxe
MXE_SKIP_INSTALL  Comma/space separated list of package names to skip
                  installing. Useful to exclude unnecessary dependencies.
                  *-linux-gnu-*, mxe-requirements, mxe-source packages
                  are excluded automatically.
MXE_INST_LINUX    Install 'linux-gnu' packages. Default: no

Required: ar (BSD), gpg, curl, openssl, awk, sed, tar, gzip

Author: Viktor Szakats"
}

mxe_curl() {
  curl -fsS --connect-timeout 15 -m 540 --retry 3 "$@"
}

mxe_get_pkg() {

  if [[ "$1" =~ ^(mxe-(i686|x86-64)-(w64|unknown)-(mingw32|linux-gnu)(.shared|.static)?)-(.*)$ ]]; then

    repo="${BASH_REMATCH[1]}"  # mxe-x86-64-w64-mingw32.shared
    plat="${BASH_REMATCH[4]}"  # mingw32 | linux-gnu
    name="${BASH_REMATCH[6]}"  # harfbuzz

    # skip Linux packages by default
    if [ ! "${plat}" = 'linux-gnu' ] || [ "${MXE_INST_LINUX}" = 'yes' ]; then

      # skip packages on the skip install list
      if [[ ! "${name}" =~ ^("${MXE_SKIP_INSTALL//[, ]/|}")$ ]]; then

        idid="${repo}-${name}"  # package id for internal purposes
        if [[ ! "${done}" = *"|${idid}|"* ]]; then  # avoid installing the same package twice
          done="${done} |${idid}|"  # add to list of install packages

          ctrl="$(awk "/^Package: ${repo}-${name}$/,/^SHA256: /" Packages)"  # control section for this package

          debp="$(echo "${ctrl}" | sed -n -E 's,^Filename: (.+)$,\1,p')"  # .deb path
          vers="$(echo "${ctrl}" | sed -n -E 's,^Version: (.+)$,\1,p')"  # package version
          hash="$(echo "${ctrl}" | sed -n -E 's,^SHA256: ([0-9a-fA-F]{64})$,\1,p')"  # .deb hash
          deps="$(echo "${ctrl}" | sed -n -E 's,^Depends: (.+)$,\1,p')"  # .deb dependencies

          echo "! Version: ${vers}"
          url="${base}/${debp}"
          echo "! Downloading... '${url}'"
          if mxe_curl "${url}" -o pack.bin; then

            hash_fl="$(openssl dgst -sha256 pack.bin \
              | sed -n -E 's,.+= ([0-9a-fA-F]{64}),\1,p')"

            if [ "${hash_fl}" = "${hash}" ]; then
              if ar -x pack.bin data.tar.xz && \
                 tar --strip-components 4 -xf data.tar.xz; then
                subd="$(echo "$(pwd)/usr/${repo}" \
                  | sed -e 's|^mxe-||' -e 's|x86-64|x86_64|' -e "s|${HOME}|~|")"
                echo "! Verified OK. Unpacked into: '${subd}'"  # ~/mxe/usr/mxe-x86_64-w64-mingw32.shared
              else
                echo "! Error: Unpacking: '${url}'"
              fi
              rm -f data.tar.xz
            else
              echo "! Error: Verifying package checksum: '${url}'"
              echo "!        Expected: ${hash}"
              echo "!          Actual: ${hash_fl}"
            fi
            rm -f pack.bin

            for i in ${deps//,/}; do
              mxe_get_pkg "${i}"  # recurse
            done
          else
            echo "! Error: Download failed."
          fi
        fi
      fi
    fi
  elif [ ! "$1" = 'mxe-requirements' ] && \
       [ ! "$1" = 'mxe-source' ]; then
    echo "! Error: Cannot parse package name: '$1'"
  fi
}

if [ $# -eq 0 ]; then
  usage
  exit
fi

[ -z "${MXE_SKIP_INSTALL+x}" ] && MXE_SKIP_INSTALL='gcc'
[ -z "${MXE_INST_LINUX+x}" ] && MXE_INST_LINUX='no'
[ -z "${MXE_HOME+x}" ] && MXE_HOME="${HOME}/mxe"

mkdir -p "${MXE_HOME}"
(
  cd "${MXE_HOME}" || exit

  base='https://pkg.mxe.cc/repos/apt/debian'  # APT root
  suid='D43A795B73B16ABE9643FE1AFD8FFF16DB45C6AB'  # Signer UID

  alias gpg='gpg --batch --keyid-format LONG'

  echo "! Downloading and verifying MXE package list..."
  mxe_curl \
    -O "${base}/dists/wheezy/Release.gpg" \
    -O "${base}/dists/wheezy/Release"
  (
    set -x
    mxe_curl \
      "https://keyserver.ubuntu.com/pks/lookup?search=0x${suid}&op=get" \
    | gpg --import --status-fd 1
  )
  gpg --verify-options show-primary-uid-only --verify Release.gpg Release || exit 1
  mxe_curl \
    -O "${base}/dists/wheezy/main/binary-amd64/Packages.gz"
  openssl dgst -sha256 Packages.gz \
  | grep -q "$(sed -E -n 's,^ ([0-9a-fA-F]{64}) [0-9]* main/binary-amd64/Packages.gz$,\1,p' Release)" || exit 1
  gzip -f -d Packages.gz

  echo "! Downloading and verifying MXE package(s)..."
  done=''
  while [ $# -gt 0 ]; do
    echo "! Installing MXE package '$1'"
    mxe_get_pkg "$1"
    shift
  done
  echo "! Installed:${done//|/}"

  if [ -n "${done}" ]; then
    ori='/usr/lib/mxe'
    pwd="$(pwd)"

    echo '! Retargeting symlinks...'
    find . -type l -name '*' | while IFS= read -r f; do
      # FIXME: readlink may need to be adapted for non-macOS systems
      ln -f -s "$(readlink "${f}" | sed "s|${ori}|${pwd}|")" "${f}"
    done

    echo '! Rewriting hardcoded absolute paths...'
    find . -type f \
      -name '*.la' -o \
      -name '*.pc' -o \
      -name '*.cmake' -o \
      -name '*.prf' -o \
      -name '*.pri' -o \
      -name '*.prl' -o \
      -name '*-config' | while IFS= read -r f; do

      sed "s|${ori}|${pwd}|" \
        < "${f}" > "${f}-mod" && cp "${f}-mod" "${f}" && rm -f "${f}-mod"
    done
  fi

  echo '! Done.'
)
