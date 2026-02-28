# pypour

Un transpileur Python en fran\u00e7ais. \u00c9crivez du Python avec des mots-cl\u00e9s et des fonctions int\u00e9gr\u00e9es en fran\u00e7ais, puis ex\u00e9cutez-le directement ou transpilez-le en Python standard.

## Installation

### Version C (recommand\u00e9e)

```bash
make
```

Cela construit `pypour-bin` \u2014 un ex\u00e9cutable autonome sans d\u00e9pendances au-del\u00e0 de `python3` (utilis\u00e9 pour ex\u00e9cuter le code transpil\u00e9).

### Version Python

```bash
pip install -e .
```

## Utilisation

Ex\u00e9cuter un fichier `.ppour` :
```bash
pypour run fichier.ppour
```

Transpiler en Python (afficher sur stdout) :
```bash
pypour transpile fichier.ppour
```

Ex\u00e9cuter et sauvegarder la sortie transpil\u00e9e :
```bash
pypour run fichier.ppour -o sortie.py
```

## Exemple

```python
# bonjour.ppour

fonction saluer(nom):
    afficher("Bonjour, " + nom + "!")

pour i dans portee(3):
    saluer("monde")

si vrai:
    afficher("C'est vrai!")
sinon:
    afficher("C'est faux!")
```

## Mots-cl\u00e9s fran\u00e7ais

| Fran\u00e7ais | Python |
|--------|--------|
| si | if |
| sinon | else |
| sinonsi | elif |
| tantque | while |
| pour | for |
| dans | in |
| fonction | def |
| retourner | return |
| classe | class |
| importer | import |
| depuis | from |
| comme | as |
| et | and |
| ou | or |
| non | not |
| vrai | True |
| faux | False |
| rien | None |
| essayer | try |
| sauf | except |
| finalement | finally |
| lever | raise |
| avec | with |
| passer | pass |
| continuer | continue |
| casser | break |

## Fonctions int\u00e9gr\u00e9es fran\u00e7aises

| Fran\u00e7ais | Python |
|--------|--------|
| afficher | print |
| saisir | input |
| longueur | len |
| portee | range |
| entier | int |
| flottant | float |
| chaine | str |
| liste | list |
| dico | dict |
| ensemble | set |
| booleen | bool |
| ouvrir | open |
| enumerer | enumerate |
| trier | sorted |
| carte | map |
| filtrer | filter |
| somme | sum |
| tout | all |
| nimporte | any |

## Messages d'erreur

Les erreurs sont traduites en fran\u00e7ais :
```
ErreurDeNom: 'x' n'est pas d\u00e9fini
ErreurDeSyntaxe: syntaxe invalide
ErreurDeDivisionParZ\u00e9ro: division par z\u00e9ro
```

---

# English

A French-localized Python transpiler. Write Python using French keywords and builtins, then run it directly or transpile it to standard Python.

## Installation

### C version (recommended)

```bash
make
```

This builds `pypour-bin` \u2014 a standalone binary with no dependencies beyond `python3` (used to execute transpiled code).

### Python version

```bash
pip install -e .
```

## Usage

Run a `.ppour` file:
```bash
pypour run fichier.ppour
```

Transpile to Python (print to stdout):
```bash
pypour transpile fichier.ppour
```

Run and save the transpiled output:
```bash
pypour run fichier.ppour -o sortie.py
```

## Example

```python
# bonjour.ppour

fonction saluer(nom):
    afficher("Bonjour, " + nom + "!")

pour i dans portee(3):
    saluer("monde")

si vrai:
    afficher("C'est vrai!")
sinon:
    afficher("C'est faux!")
```

## French Keywords

| French | Python |
|--------|--------|
| si | if |
| sinon | else |
| sinonsi | elif |
| tantque | while |
| pour | for |
| dans | in |
| fonction | def |
| retourner | return |
| classe | class |
| importer | import |
| depuis | from |
| comme | as |
| et | and |
| ou | or |
| non | not |
| vrai | True |
| faux | False |
| rien | None |
| essayer | try |
| sauf | except |
| finalement | finally |
| lever | raise |
| avec | with |
| passer | pass |
| continuer | continue |
| casser | break |

## French Builtins

| French | Python |
|--------|--------|
| afficher | print |
| saisir | input |
| longueur | len |
| portee | range |
| entier | int |
| flottant | float |
| chaine | str |
| liste | list |
| dico | dict |
| ensemble | set |
| booleen | bool |
| ouvrir | open |
| enumerer | enumerate |
| trier | sorted |
| carte | map |
| filtrer | filter |
| somme | sum |
| tout | all |
| nimporte | any |

## Error Messages

Errors are translated to French:
```
ErreurDeNom: 'x' n'est pas d\u00e9fini
ErreurDeSyntaxe: syntaxe invalide
ErreurDeDivisionParZ\u00e9ro: division par z\u00e9ro
```
