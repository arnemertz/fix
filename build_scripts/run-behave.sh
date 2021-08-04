#! /usr/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

pushd "${SCRIPT_DIR}/../behave" > /dev/null || exit

# run all scenarios that are not tagged @skip AND all that are tagged @wip
docker4c run behave -t ~skip,wip

popd > /dev/null || exit