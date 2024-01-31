Nous souhaitons réaliser un système de vote électronique reposant sur une blockchain comme moyen d'enregistrer les transactions de vote.

La conception et la mise en œuvre d'un système de vote basé sur la blockchain nécessitent une expertise dans divers domaines, notamment la cryptographie, les systèmes distribués et la programmation en C.

Nous allons présenter les concepts nécessaires dans ces différents domaines tout au long des séances de travaux pratiques.

## Ce que nous avons fait

Actuellement nous avons réussi à implémenter de multiples fonctionnalitées :

- **Cryptographie** : Nous avons ajouté un système de cryptographie à notre serveur qui permet de décrypter les votes que l'on reçoit

- **Pattern command** : Nous avons réalisé un command pattern dans notre serveur, chaque commande lance un handler réalisant la commande.

- **Future API** : L'API Future a été mise en place dans notre projet, elle nous permet de gérer plus précisément le début et la fin d'un handler.

- **Communication avec la base de données SQLite** : Nous avons réussi à faire communiquer

## Ce qu'il reste à faire

- **Communication client/serveur** : Nous avons développé la base du serveur de vote de notre application, il manque un client et une communication avec les sockets entre les clients et les serveurs.

- **Client** : Le client qui nous manque doit envoyer un vote crypté avec son ID, la clé de chiffrement et la commande qu'il souhaite faire.
