import argparse
import sys
from .transpiler import transpile_file
from .errors import print_french_error


def cmd_run(args):
    try:
        python_source = transpile_file(args.file)
    except FileNotFoundError:
        print(f"Erreur: fichier '{args.file}' introuvable.", file=sys.stderr)
        sys.exit(1)

    namespace = {"__name__": "__main__"}
    try:
        exec(compile(python_source, args.file, "exec"), namespace)
    except SystemExit:
        raise
    except Exception as exc:
        print_french_error(exc, args.file)
        sys.exit(1)


def cmd_transpile(args):
    try:
        python_source = transpile_file(args.file)
    except FileNotFoundError:
        print(f"Erreur: fichier '{args.file}' introuvable.", file=sys.stderr)
        sys.exit(1)

    print(python_source)


def main():
    parser = argparse.ArgumentParser(
        prog="pypour",
        description="pypour — transpileur Python francophone",
    )
    sub = parser.add_subparsers(dest="command")

    run_p = sub.add_parser("run", help="Exécuter un fichier .ppour")
    run_p.add_argument("file", help="Chemin vers le fichier .ppour")

    tr_p = sub.add_parser("transpile", help="Afficher le Python généré")
    tr_p.add_argument("file", help="Chemin vers le fichier .ppour")

    args = parser.parse_args()
    if args.command == "run":
        cmd_run(args)
    elif args.command == "transpile":
        cmd_transpile(args)
    else:
        parser.print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
