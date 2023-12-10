# Ultra-cp

## 1. Introduction

Ce rapport détaille un programme de copie de fichiers conçu pour fonctionner avec une variété de types de fichiers, incluant des fichiers réguliers, des liens et des dossiers. Le programme est structuré en plusieurs modules, chacun gérant des aspects spécifiques de la copie, de l'analyse des options de ligne de commande à la récupération des informations de fichiers.

## 2. Architecture du Programme

### Décomposition Modulaire

1. **copy.c & copy.h** : Gère la logique principale de copie des fichiers et des dossiers, incluant les options de copie avancées.
2. **func.c & func.h** : Fournit des utilitaires pour la manipulation de fichiers, tels que la liste des fichiers dans un répertoire.
3. **option.c & option.h** : Analyse les options de ligne de commande fournies par l'utilisateur.
4**main.c** : Coordonne les opérations globales et fait appel aux autres modules en fonction des entrées de l'utilisateur.

### Structures de Données Utilisées

- Utilisation de structures standard C pour la manipulation de fichiers (`FILE`, descripteurs de fichiers) et les informations sur les fichiers (`struct stat`).
- Variables simples et pointeurs pour stocker les résultats de l'analyse des options de ligne de commande et l'état du programme.

### Fonctionnalité et Mécanismes

- **Gestion de la Copie** : `copyFile` et `ultraCP` dans `copy.c` gèrent les opérations de copie, y compris la copie de dossiers et la gestion des liens.
- **Utilitaires de Fichiers** : `func.c` fournit des fonctions pour interpréter les types et permissions des fichiers.
- **Analyse des Options** : `option.c` parse les options de ligne de commande et définit les paramètres du programme.

