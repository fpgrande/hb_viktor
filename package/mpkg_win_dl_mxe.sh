#!/usr/bin/env bash

# ---------------------------------------------------------------
# Copyright 2017 Viktor Szakats (vszakats.net/harbour)
# See LICENSE.txt for licensing terms.
# ---------------------------------------------------------------

# Download and unpack an mxe binary package

# TOFIX: no checksum/signature verification whatsoever

mxe_get_pkg() {
  if [[ "$1" =~ ^(mxe-(i686|x86\-64)-w64-mingw32\.(shared|static))-(.*)$ ]]; then
    repo="${BASH_REMATCH[1]}"
    name="${BASH_REMATCH[4]}"
    base='http://pkg.mxe.cc/repos/tar/'
    dirl="$(curl -fsS "${base}${repo}/")"
    if [[ "${dirl}" =~ (${repo}-${name}_([0-9.]*).tar.xz) ]]; then
      echo "! Version: ${BASH_REMATCH[2]}"
      if curl -fsS "${base}${repo}/${BASH_REMATCH[1]}" \
         | tar -x; then
        subd="$(echo "$(pwd)/usr/${repo}" | sed 's|^mxe-||' | sed 's|x86-64|x86_64|' | sed "s|${HOME}|~|")"
        echo "! OK. Installed into '${subd}'"
      fi
    fi
  fi
}

echo '! WARNING: No checksum/signature verification and cleartext download protocol.'

mkdir -p "${HOME}/mxe"
(
  cd "${HOME}/mxe" || exit

  while [ -n "$1" ]; do
    echo "! Downloading and unpacking $1..."
    mxe_get_pkg "$1"
    shift
  done
)