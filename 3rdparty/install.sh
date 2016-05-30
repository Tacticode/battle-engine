#!/bin/bash

DEPOT_TOOLS_PATH="3rdparty/depot_tools"
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git $DEPOT_TOOLS_PATH || echo "depot tools already fetched?";

"$DEPOT_TOOLS_PATH"/gclient;
cd 3rdparty;
export PATH="`pwd`/depot_tools/":"$PATH";
echo "Fetching V8 you may have to wait for a moment";
"depot_tools"/fetch v8;
"depot_tools"/gclient sync;

