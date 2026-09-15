#!/usr/bin/env bash
# Build one project (or all of them) exactly the way CI does.
#
#   .github/scripts/build.sh Webserv
#   .github/scripts/build.sh all
#
# Every project is built with its own Makefile and -Wall -Wextra -Werror.
# Minishell needs libreadline-dev; Cub3D and so_long need cmake + libglfw3-dev.
set -euo pipefail
cd "$(dirname "$0")/../.."

ALL=(Libft get_next_line ft_printf pipex push_swap Philosophers Minishell Webserv
     CPP00 CPP01 CPP02 CPP03 CPP04 CPP05 CPP06 CPP07 CPP08 CPP09 so_long Cub3D)

build() {
    echo "::group::$1"
    case "$1" in
        get_next_line)
            (cd get_next_line && cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
                -c get_next_line.c get_next_line_utils.c && rm -f ./*.o) ;;
        Philosophers)
            make -C Philosophers/philo && make -C Philosophers/philo fclean ;;
        CPP*)
            for ex in "$1"/ex*/; do
                make -C "$ex" && make -C "$ex" fclean
            done ;;
        *)
            make -C "$1" && make -C "$1" fclean ;;
    esac
    echo "::endgroup::"
}

if [ "${1:-all}" = all ]; then
    for p in "${ALL[@]}"; do build "$p"; done
else
    build "$1"
fi
