#!/usr/bin/env bash

BIN="$(dirname "${BASH_SOURCE[0]}")/../scop"

$BIN /dev/null

$BIN /dev/random
