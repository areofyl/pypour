# pypour

A French-localized Python transpiler. Write Python using French keywords and builtins, then run it directly or transpile it to standard Python.

## Installation

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
ErreurDeDivisionParZero: division par zéro
```
