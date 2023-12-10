# TP3 : Gestion des Verrous de Fichier en C

## 1. Introduction
Durant ce TP, j'ai développé un programme en C pour manipuler des verrous de fichier. Ce programme permet de poser et de retirer des verrous sur des portions spécifiques d'un fichier de manière interactive.

## 2. Description
Les verrous de fichier sont essentiels pour la coordination de l'accès concurrent à des fichiers par différents processus. Il existe deux types principaux de verrous : coopératifs et obligatoires. J'ai utilisé la fonction `fcntl()` de Linux dans ce TP car elle offre la flexibilité de verrouiller des parties spécifiques d'un fichier. Le programme est lancé avec un fichier en argument, comme : `./lock fichier.txt`. Une fois démarré, il propose diverses interactions avec le fichier.

Exemple d'interaction :
```
$ ./lock fichier.txt
Enter '?' for help and 'q' to quit
PID=1234> s r 0 10
[PID=1234] a posé un verrou en lecture de 0 à 10
PID=1234> q
```

## 3. Utilisation de `flock()`
La fonction `flock()` sert à poser des verrous coopératifs. Toutefois, elle ne permet que le verrouillage complet d'un fichier, pas de ses parties. C'est pourquoi je ne l'ai pas utilisée dans mon implémentation.

## 4. Utilisation de `fcntl()`
J'ai principalement utilisé `fcntl()` pour ses capacités de verrouillage plus granulaires. Elle est utilisée comme suit :
- `F_GETLK` : Vérifie si un verrou peut être posé. Si possible, `l_type` dans `struct flock` devient `F_UNLCK`, sinon la structure est remplie avec les informations du verrou en conflit.
- `F_SETLK` et `F_SETLKW` : Posent ou retirent un verrou. `F_SETLKW` bloque si le verrou ne peut être posé immédiatement.
- La structure `struct flock` utilisée comprend plusieurs champs, dont `l_type`, `l_whence`, `l_start`, `l_len`, et `l_pid`.

## 5. Observations et Conclusion
- Déverrouiller une section non verrouillée se comporte comme si elle était verrouillée.
- Poser un verrou sur une section déjà verrouillée dépend du type de verrou et du contexte (un ou plusieurs processus).
- Mon implémentation affiche des messages après chaque opération de verrouillage pour indiquer le succès ou l'échec de l'opération.

**Sources** :
- Documentation Linux
- Cours sur les I/O en système d'exploitation
- Supports de cours du TP3

