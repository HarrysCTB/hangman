# 🎮 Jeu du Pendu en C

Bienvenue dans ma version interactive et entièrement jouable en ligne de commande du jeu classique du pendu ! Ce projet a été soigneusement conçu en langage C pour offrir une expérience amusante et stimulante directement depuis votre terminal.

## 🌟 Introduction

Le jeu du pendu est un jeu de devinettes classique où le joueur tente de deviner un mot en proposant des lettres. À chaque fois qu'une lettre proposée n'est pas dans le mot, une partie du pendu est dessinée. Le but est de deviner le mot avant que le dessin du pendu ne soit complété.

Dans notre version :

• **Dictionnaire de Mots :** Le jeu utilise un fichier texte contenant un vaste ensemble de mots. Le nom de ce fichier est spécifié en argument lors du lancement du programme, permettant une grande flexibilité et une variété de mots.

• **Trois Niveaux de Difficulté :** Pour s'adapter à tous les joueurs, notre jeu offre trois niveaux de difficulté. Chaque niveau ajuste les paramètres du jeu, comme le nombre de tentatives autorisées et la complexité des mots, pour offrir un défi approprié à tous.

• **100% Terminal :** Conçu pour être joué entièrement dans le terminal, ce jeu du pendu offre une expérience nostalgique et authentique qui rappelle les débuts de l'informatique ludique.

## 🚀 Par où Commencer ?


```
git clone https://github.com/HarrysCTB/hangman.git
cd hangman
make re
./hangman <dictionnaire.txt> <facile/moyen/difficile> <categories>
```

## 📜 Règles du Jeu

Le jeu du pendu est un classique des devinettes, et notre version en C ajoute une touche moderne à ce jeu intemporel. Voici comment il fonctionne :

• **Sélection du Mot :** Au début de chaque partie, un mot est choisi au hasard dans le dictionnaire. Si nécessaire, le mot peut être sélectionné à partir d'une catégorie spécifique, ajoutant ainsi un élément de surprise et de défi.

• **Affichage du Mot :** Le mot à deviner est affiché sur votre écran, avec les lettres masquées par des astérisques (*). Tous les autres caractères, comme les espaces et les traits d’union, sont visibles. Cela aide à deviner la structure du mot.

• **Indication de la Catégorie :** La catégorie du mot est également affichée, donnant un indice supplémentaire pour faciliter la devinette.

• **Le Dessin du Pendu :** À chaque erreur, une partie du pendu est dessinée sur la potence. Cette représentation visuelle permet de suivre le nombre d'erreurs commises.

• **Limite d'Erreurs :** Vous avez droit à six erreurs. À la sixième erreur, la partie est perdue et le programme s'arrête.

• **Victoire et Continuation :** Si vous parvenez à deviner le mot avant que le pendu ne soit complètement dessiné, vous gagnez ! Le programme vous demandera alors si vous souhaitez jouer une nouvelle partie. Répondez par 'Y' pour oui ou 'N' pour non.

## 🎥 Démonstration

![Coming Soon](https://media.giphy.com/media/z6EG2su1f5jOTourNL/giphy.gif)

## 🛠️ Technologie utilisée

• C

## ✨ Fonctionnalités

![Coming Soon](https://media.giphy.com/media/z6EG2su1f5jOTourNL/giphy.gif)

## 📚 Documentation

• [Documentation langage C](https://en.cppreference.com/w/c).

## 👨‍💻 Contributeurs

![Coming Soon](https://media.giphy.com/media/z6EG2su1f5jOTourNL/giphy.gif)

## 🤝 Contribuer

Nous accueillons et apprécions les contributions de tous ceux qui souhaitent améliorer et enrichir le jeu du pendu en C. Que vous soyez un développeur expérimenté ou un débutant passionné, votre aide est la bienvenue. Voici comment vous pouvez contribuer :

Forker le Projet : Commencez par faire un 'fork' du projet sur GitHub. Cela créera une copie du projet sur votre compte GitHub, sur laquelle vous pourrez travailler.

Proposer des Changements : Apportez vos modifications et améliorations. Cela peut inclure de nouvelles fonctionnalités, des corrections de bugs, des améliorations de performances, ou même de la documentation.

Envoyer une Pull Request : Une fois que vous êtes satisfait de vos changements, soumettez une 'pull request'. Cela nous permettra de revoir vos modifications.

Discussion et Fusion : Votre 'pull request' sera examinée. Nous pourrons discuter des modifications, et si tout est en ordre, elle sera fusionnée dans le projet principal.

Votre contribution, quelle qu'elle soit, est précieuse et contribuera à faire de ce jeu du pendu une expérience encore plus agréable pour tous.

## 📝 Licence

Ce projet est distribué sous la Licence MIT. Cette licence permet une grande flexibilité dans l'utilisation et la modification du code, tout en nécessitant que la licence originale et le droit d'auteur soient inclus dans toute distribution substantielle du code.
