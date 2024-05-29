#!/bin/sh

perror() {
	FULLNAME="${0##*/}"
	echo >&2 "${FULLNAME%.*}:" "$@"
	exit 127
}

case "$*" in
	''|*[!0-9]*) perror \
	"a single positive integer was expected: '$*'" ;;
esac


case "$(factor "$*" | wc -w)" in

	0|*[!0-9]*) perror "Unexpected 'wc -w' result!";;
	2) echo "True"; exit 0;;
	*) echo "False"; exit 1;;

esac
