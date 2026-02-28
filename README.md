# pypour

Un transpileur Python en français. Écrivez du Python avec des mots-clés et des fonctions intégrées en français, puis exécutez-le directement ou transpilez-le en Python standard.

## Installation

### Version C (recommandée)

```bash
make
```

Cela construit `pypour-bin` — un exécutable autonome sans dépendances au-delà de `python3` (utilisé pour exécuter le code transpilé).

### Version Python

```bash
pip install -e .
```

## Utilisation

Exécuter un fichier `.ppour` :
```bash
pypour run fichier.ppour
```

Transpiler en Python (afficher sur stdout) :
```bash
pypour transpile fichier.ppour
```

Exécuter et sauvegarder la sortie transpilée :
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

## Mots-clés français

| Français | Python |
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

## Fonctions intégrées françaises

| Français | Python |
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

Les erreurs sont traduites en français :
```
ErreurDeNom: 'x' n'est pas défini
ErreurDeSyntaxe: syntaxe invalide
ErreurDeDivisionParZéro: division par zéro
```

---

# English

A French-localized Python transpiler. Write Python using French keywords and builtins, then run it directly or transpile it to standard Python.

## Installation

### C version (recommended)

```bash
make
```

This builds `pypour-bin` — a standalone binary with no dependencies beyond `python3` (used to execute transpiled code).

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
ErreurDeNom: 'x' n'est pas défini
ErreurDeSyntaxe: syntaxe invalide
ErreurDeDivisionParZéro: division par zéro
```
