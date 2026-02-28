#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

/* ── Mapping tables ─────────────────────────────────────────────── */

typedef struct { const char *fr; const char *py; } Map;

static const Map keywords[] = {
    {"si",         "if"},
    {"sinon",      "else"},
    {"sinonsi",    "elif"},
    {"tantque",    "while"},
    {"pour",       "for"},
    {"dans",       "in"},
    {"fonction",   "def"},
    {"retourner",  "return"},
    {"classe",     "class"},
    {"importer",   "import"},
    {"depuis",     "from"},
    {"comme",      "as"},
    {"et",         "and"},
    {"ou",         "or"},
    {"non",        "not"},
    {"vrai",       "True"},
    {"faux",       "False"},
    {"rien",       "None"},
    {"essayer",    "try"},
    {"sauf",       "except"},
    {"finalement", "finally"},
    {"lever",      "raise"},
    {"avec",       "with"},
    {"passer",     "pass"},
    {"continuer",  "continue"},
    {"casser",     "break"},
    {"affirmer",   "assert"},
    {"supprimer",  "del"},
    {"rendement",  "yield"},
};

static const Map builtins[] = {
    {"afficher",  "print"},
    {"saisir",    "input"},
    {"longueur",  "len"},
    {"portee",    "range"},
    {"type",      "type"},
    {"entier",    "int"},
    {"flottant",  "float"},
    {"chaine",    "str"},
    {"liste",     "list"},
    {"dico",      "dict"},
    {"ensemble",  "set"},
    {"booleen",   "bool"},
    {"ouvrir",    "open"},
    {"enumerer",  "enumerate"},
    {"trier",     "sorted"},
    {"carte",     "map"},
    {"filtrer",   "filter"},
    {"somme",     "sum"},
    {"min",       "min"},
    {"max",       "max"},
    {"abs",       "abs"},
    {"tout",      "all"},
    {"nimporte",  "any"},
};

#define COUNTOF(a) (sizeof(a)/sizeof((a)[0]))

static const char *lookup(const char *id) {
    for (size_t i = 0; i < COUNTOF(keywords); i++)
        if (strcmp(id, keywords[i].fr) == 0) return keywords[i].py;
    for (size_t i = 0; i < COUNTOF(builtins); i++)
        if (strcmp(id, builtins[i].fr) == 0) return builtins[i].py;
    return NULL;
}

/* ── Error translation tables ───────────────────────────────────── */

static const Map error_names[] = {
    {"SyntaxError",         "ErreurDeSyntaxe"},
    {"NameError",           "ErreurDeNom"},
    {"TypeError",           "ErreurDeType"},
    {"ValueError",          "ErreurDeValeur"},
    {"IndexError",          "ErreurDIndex"},
    {"KeyError",            "ErreurDeCle"},
    {"AttributeError",      "ErreurDAttribut"},
    {"ZeroDivisionError",   "ErreurDeDivisionParZero"},
    {"FileNotFoundError",   "ErreurFichierIntrouvable"},
    {"ImportError",         "ErreurDImportation"},
};

static const Map error_msgs[] = {
    {"is not defined",               "n'est pas d\xc3\xa9""fini"},
    {"is not callable",              "n'est pas appelable"},
    {"unexpected indent",            "indentation inattendue"},
    {"expected an indented block",   "bloc indent\xc3\xa9 attendu"},
    {"invalid syntax",               "syntaxe invalide"},
    {"division by zero",             "division par z\xc3\xa9ro"},
    {"list index out of range",      "index de liste hors limites"},
    {"string index out of range",    "index de cha\xc3\xaene hors limites"},
    {"object has no attribute",      "l'objet n'a pas d'attribut"},
    {"takes no arguments",           "ne prend aucun argument"},
    {"missing required argument",    "argument requis manquant"},
    {"unexpected keyword argument",  "argument nomm\xc3\xa9 inattendu"},
    {"object is not iterable",       "l'objet n'est pas it\xc3\xa9rable"},
    {"object is not subscriptable",  "l'objet n'est pas indexable"},
    {"can't convert",                "impossible de convertir"},
    {"invalid literal for",          "valeur litt\xc3\xa9rale invalide pour"},
    {"No module named",              "Aucun module nomm\xc3\xa9"},
    {"No such file or directory",    "Aucun fichier ou r\xc3\xa9pertoire de ce nom"},
};

/* Also translate Python identifiers back to French in error messages */
static const char *reverse_lookup(const char *id) {
    for (size_t i = 0; i < COUNTOF(keywords); i++)
        if (strcmp(id, keywords[i].py) == 0) return keywords[i].fr;
    for (size_t i = 0; i < COUNTOF(builtins); i++)
        if (strcmp(id, builtins[i].py) == 0) return builtins[i].fr;
    return NULL;
}

/* ── Dynamic buffer ─────────────────────────────────────────────── */

typedef struct {
    char  *data;
    size_t len;
    size_t cap;
} Buf;

static void buf_init(Buf *b) {
    b->cap = 4096;
    b->data = malloc(b->cap);
    b->len = 0;
}

static void buf_push(Buf *b, char c) {
    if (b->len + 1 >= b->cap) {
        b->cap *= 2;
        b->data = realloc(b->data, b->cap);
    }
    b->data[b->len++] = c;
}

static void buf_write(Buf *b, const char *s, size_t n) {
    while (b->len + n >= b->cap) b->cap *= 2;
    b->data = realloc(b->data, b->cap);
    memcpy(b->data + b->len, s, n);
    b->len += n;
}

static void buf_writes(Buf *b, const char *s) {
    buf_write(b, s, strlen(s));
}

static void buf_free(Buf *b) { free(b->data); }

/* ── Transpiler ─────────────────────────────────────────────────── */

static int is_id_start(char c) {
    return isalpha((unsigned char)c) || c == '_';
}

static int is_id_char(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

static char *transpile(const char *src, size_t srclen) {
    Buf out;
    buf_init(&out);

    size_t i = 0;
    while (i < srclen) {
        char c = src[i];

        /* Comment: copy until newline */
        if (c == '#') {
            while (i < srclen && src[i] != '\n')
                buf_push(&out, src[i++]);
            continue;
        }

        /* String literals */
        if (c == '\'' || c == '"') {
            /* Check for triple quote */
            int triple = (i + 2 < srclen && src[i+1] == c && src[i+2] == c);
            if (triple) {
                /* Copy opening triple */
                buf_push(&out, c); buf_push(&out, c); buf_push(&out, c);
                i += 3;
                /* Copy until closing triple */
                while (i < srclen) {
                    if (src[i] == '\\' && i + 1 < srclen) {
                        buf_push(&out, src[i++]);
                        buf_push(&out, src[i++]);
                    } else if (src[i] == c && i + 2 < srclen && src[i+1] == c && src[i+2] == c) {
                        buf_push(&out, c); buf_push(&out, c); buf_push(&out, c);
                        i += 3;
                        break;
                    } else {
                        buf_push(&out, src[i++]);
                    }
                }
            } else {
                /* Single-quoted string */
                char q = c;
                buf_push(&out, src[i++]);
                while (i < srclen && src[i] != q) {
                    if (src[i] == '\\' && i + 1 < srclen) {
                        buf_push(&out, src[i++]);
                        buf_push(&out, src[i++]);
                    } else if (src[i] == '\n') {
                        /* Unterminated string — just stop */
                        break;
                    } else {
                        buf_push(&out, src[i++]);
                    }
                }
                if (i < srclen) buf_push(&out, src[i++]); /* closing quote */
            }
            continue;
        }

        /* Identifier */
        if (is_id_start(c)) {
            size_t start = i;
            while (i < srclen && is_id_char(src[i])) i++;
            size_t idlen = i - start;

            /* Copy identifier to temp buffer for lookup */
            char idbuf[256];
            if (idlen < sizeof(idbuf)) {
                memcpy(idbuf, src + start, idlen);
                idbuf[idlen] = '\0';
                const char *repl = lookup(idbuf);
                if (repl)
                    buf_writes(&out, repl);
                else
                    buf_write(&out, src + start, idlen);
            } else {
                buf_write(&out, src + start, idlen);
            }
            continue;
        }

        /* Everything else: copy verbatim */
        buf_push(&out, src[i++]);
    }

    buf_push(&out, '\0');
    return out.data;
}

/* ── File reading ───────────────────────────────────────────────── */

static char *read_file(const char *path, size_t *outlen) {
    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "pypour: impossible d'ouvrir '%s'\n", path);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len + 1);
    size_t rd = fread(buf, 1, len, f);
    buf[rd] = '\0';
    fclose(f);
    if (outlen) *outlen = rd;
    return buf;
}

/* ── Error translation ──────────────────────────────────────────── */

/* Replace all occurrences of `from` with `to` in a string, returning new alloc */
static char *str_replace_all(const char *haystack, const char *from, const char *to) {
    size_t fromlen = strlen(from);
    size_t tolen   = strlen(to);

    /* Count occurrences */
    size_t count = 0;
    const char *p = haystack;
    while ((p = strstr(p, from)) != NULL) { count++; p += fromlen; }

    size_t newlen = strlen(haystack) + count * (tolen - fromlen);
    char *result = malloc(newlen + 1);
    char *dst = result;
    p = haystack;
    while (*p) {
        const char *match = strstr(p, from);
        if (!match) {
            strcpy(dst, p);
            dst += strlen(p);
            break;
        }
        memcpy(dst, p, match - p);
        dst += match - p;
        memcpy(dst, to, tolen);
        dst += tolen;
        p = match + fromlen;
    }
    *dst = '\0';
    return result;
}

static char *translate_errors(const char *stderr_text) {
    char *result = strdup(stderr_text);

    /* Replace error type names */
    for (size_t i = 0; i < COUNTOF(error_names); i++) {
        char *tmp = str_replace_all(result, error_names[i].fr, error_names[i].py);
        free(result);
        result = tmp;
    }

    /* Replace message fragments */
    for (size_t i = 0; i < COUNTOF(error_msgs); i++) {
        char *tmp = str_replace_all(result, error_msgs[i].fr, error_msgs[i].py);
        free(result);
        result = tmp;
    }

    /* Replace Python identifiers with French equivalents in quoted names */
    /* e.g. name 'print' is not defined -> name 'afficher' ... */
    for (size_t i = 0; i < COUNTOF(keywords); i++) {
        char eng[256], fra[256];
        snprintf(eng, sizeof(eng), "'%s'", keywords[i].py);
        snprintf(fra, sizeof(fra), "'%s'", keywords[i].fr);
        char *tmp = str_replace_all(result, eng, fra);
        free(result);
        result = tmp;
    }
    for (size_t i = 0; i < COUNTOF(builtins); i++) {
        /* Skip identity mappings */
        if (strcmp(builtins[i].fr, builtins[i].py) == 0) continue;
        char eng[256], fra[256];
        snprintf(eng, sizeof(eng), "'%s'", builtins[i].py);
        snprintf(fra, sizeof(fra), "'%s'", builtins[i].fr);
        char *tmp = str_replace_all(result, eng, fra);
        free(result);
        result = tmp;
    }

    return result;
}

/* ── Run mode ───────────────────────────────────────────────────── */

static int run_transpiled(const char *pycode, const char *outpath) {
    /* Optionally save transpiled output */
    if (outpath) {
        FILE *f = fopen(outpath, "w");
        if (!f) {
            fprintf(stderr, "pypour: impossible d'\xc3\xa9""crire '%s'\n", outpath);
            return 1;
        }
        fputs(pycode, f);
        fclose(f);
    }

    /* Build command: python3 -c '...'
     * We use a temp file instead to avoid shell escaping issues */
    char tmppath[] = "/tmp/pypour_XXXXXX";
    int fd = mkstemp(tmppath);
    if (fd < 0) { perror("mkstemp"); return 1; }
    FILE *tmp = fdopen(fd, "w");
    fputs(pycode, tmp);
    fclose(tmp);

    /* Create stderr capture file */
    char cmd[512];
    char errpath[] = "/tmp/pypour_err_XXXXXX";
    int efd = mkstemp(errpath);
    if (efd < 0) { perror("mkstemp"); remove(tmppath); return 1; }
    close(efd);

    snprintf(cmd, sizeof(cmd), "python3 '%s' 2>'%s'", tmppath, errpath);
    int status = system(cmd);

    /* Read and translate stderr */
    size_t errlen;
    char *errtext = read_file(errpath, &errlen);
    if (errtext && errlen > 0) {
        char *translated = translate_errors(errtext);
        fprintf(stderr, "%s", translated);
        free(translated);
    }
    free(errtext);

    remove(tmppath);
    remove(errpath);

    /* Return python's exit code */
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return status ? 1 : 0;
}

/* ── CLI ────────────────────────────────────────────────────────── */

static void usage(void) {
    fprintf(stderr,
        "Usage: pypour <commande> <fichier.ppour> [options]\n"
        "\n"
        "Commandes:\n"
        "  run <fichier>              Transpiler et ex\xc3\xa9""cuter\n"
        "  transpile <fichier>        Afficher le Python g\xc3\xa9n\xc3\xa9r\xc3\xa9\n"
        "\n"
        "Options:\n"
        "  -o <fichier>               Sauvegarder la sortie transpil\xc3\xa9""e\n"
    );
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage();
        return 1;
    }

    const char *command = argv[1];
    const char *filepath = argv[2];
    const char *outpath = NULL;

    /* Parse -o flag */
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outpath = argv[i + 1];
            i++;
        }
    }

    /* Read source file */
    size_t srclen;
    char *src = read_file(filepath, &srclen);
    if (!src) return 1;

    /* Transpile */
    char *pycode = transpile(src, srclen);
    free(src);

    if (strcmp(command, "run") == 0) {
        int ret = run_transpiled(pycode, outpath);
        free(pycode);
        return ret;
    } else if (strcmp(command, "transpile") == 0) {
        printf("%s", pycode);
        if (outpath) {
            FILE *f = fopen(outpath, "w");
            if (f) { fputs(pycode, f); fclose(f); }
        }
        free(pycode);
        return 0;
    } else {
        fprintf(stderr, "pypour: commande inconnue '%s'\n", command);
        usage();
        free(pycode);
        return 1;
    }
}
