Projet-C : Florimond CARON && Damien MATHIEU && Samy OFFER && Raphaël Malka
--------

## Ce que nous avons fait

Actuellement nous avons réussi à implémenter de multiples fonctionnalitées :

- **Cryptographie** : Nous avons ajouté un système de cryptographie à notre serveur qui permet de décrypter les votes que l'on reçoit

- **Pattern command** : Nous avons réalisé un command pattern dans notre serveur, chaque commande lance un handler réalisant la commande.

- **Future API** : L'API Future a été mise en place dans notre projet, elle nous permet de gérer plus précisément le début et la fin d'un handler.

- **Communication avec la base de données SQLite** : Nous avons réussi à faire communiquer

- **Communication client/serveur** : Nous avons développé la base du serveur de vote de notre application. Ainsi qu'un serveur qui écoute les connnections de clients sur le port 12345. Les clients doivent envoyer des chaînes de caractères correspondant aux commandes qu'il souhaite effectuer.

- **Tests** : Nous avons developpé une séries de tests pour nous assurer du bon fonctionnement des différentes fonctionalitées. Les tests sont présents dans le dossier build lorsqu'un make est effectué.

## Ce qu'il reste à faire

- **Client** : Le client qui nous manque doit envoyer un vote crypté avec son ID, la clé de chiffrement et la commande qu'il souhaite faire.


## Pour executer le projet

- Installer les dépendences

```bash
sudo apt install libglib2.0-dev sqlite3 libsqlite3-dev
```

- Se Positionner dans ./code

- Executer le makefile

```bash
make clean
make
```

- Se positionner dans ./code/build

- Executer le serveur

```bash
./serveur
```

- Pour tester d'envoyer des commandes au serveur on peut utiliser la commande netcat

```bash
nc localhost 12345 -vv
```

- Ecrire dans l'entrée standard du terminal une commande par exemple : AJOUT_ELECTEUR

