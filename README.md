# Consignes
Les documents, l'accès à Internet et l'usage des postes personnels est autorisé. L'usage d'outils d'intelligence artificielle (Copilot compris) est interdit.
La lecture intégrale du sujet est nécessaire avant de commencer à développer.
La partie 1 consiste en une explication du flux global de l'application – il ne s'agit pas des consignes de développement, mais d'une réflexion sur l'exécution coté utilisateur.
La partie 2 décrit les classes nécessaires, ainsi que les tests à réaliser. C'est cette partie qui spécifie quoi développer.
Les annexes précisent différentes aides et consignes en lien avec l'épreuve.
Il est important que vous travailliez en suivant une logique incrémentale : démarrez par la partie "tracé de droite" avant d'ajouter et d'adapter votre code pour la suite, tout en créant un code modulable. N'essayez pas de TOUT faire directement.
Le résultat attendu doit être placé dans un dépôt github nommé "polytech-dijon-3a-cpp" privé, avec ajout en collaborateurs suivants : "esirem-chassel" et "cmeunier-ub". Un makefile ou un cmakelist doit être présent, valide et configuré pour générer l'exécutable final (nommé "tracer") dans un dossier "final".

# 1.0	Objectif
L'objectif est de réaliser une application console capable de réaliser des tracés dans un format d'image, à partir de consignes données.

## 1.1	Démarrage
Lors du démarrage de l'application en console, une question est posée "Voulez-vous tracer une nouvelle forme ou générer un résultat ?". En fonction de la réponse, un processus est lancé : tracé ou génération.

## 1.2	Tracé d'une forme
Tous les tracés se basent sur un système de coordonnées entières. La coordonnée 0, 0 (origine) est située en haut à gauche de l'image qui sera générée.
Les formes suivantes doivent être gérées :
*	Droite, à partir de deux coordonnées
*	Cercle, à partir de la coordonnée du centre et du rayon
*	Polygone, qui permet la saisie d'un nombre indéfini de points qui seront reliés par la suite
Une fois la forme "tracée" (gardée en mémoire), on revient à l'étape 1.1, afin de laisser l'utilisateur tracer autant de formes qu'il le souhaite.

## 1.3	Génération
Une fois que l'utilisateur arrête de tracer des formes et souhaite générer une image, on lui proposera le format BMP (fichier), SVG (texte) et SVG (fichier). Les formats fichiers permettront d'enregistrer un fichier sur le disque. Le format texte permet d'afficher dans la console le texte nécessaire pour l'image SVG.
 
# 2.0	Détail des attendus
En plus des attendus demandés, vous pouvez ajouter autant de classes, méthodes, propriétés et variables que nécessaire. Il est attendu un respect des bonnes pratiques (encapsulation, moindre responsabilité…).
ATTENTION : choisissez judicieusement l'ordre de réalisation de vos classes. Il est conseillé de commencer par les classes Droite et SVGgenerateurTexte (ainsi que des classes nécessaires pour ces deux classes).

## 2.1	Classes

### 2.1.1	Classe Point
Cette classe permet simplement de représenter un point avec des coordonnées X,Y.

### 2.1.2	Classe Canvas
Cette classe définit une zone de tracé. Deux propriétés "largeur" et "hauteur" sont attendues, ainsi qu'une liste de formes. Cette classe contient une propriété "fond" définissant la couleur de fond. Si elle est absente, le fond restera transparent (sans fond).
Cette classe doit surcharger l'opérateur << afin d'afficher la liste des formes contenues.

### 2.1.3	Classe Forme
La classe Forme sera la classe de base, de laquelle hériteront les différentes classes de tracé. On ne doit pas pouvoir créer d'objet Forme (mais on peut créer des objets Droite, Cercle…).
Cette classe définit une méthode abstraite "demander()" qui permet de demander, en console, à l'utilisateur de saisir les paramètres nécessaires pour la forme. Une autre méthode abstraite nécessaire est "afficher()" qui permet de décrire de manière textuelle la forme (par exemple, "cercle de centre [5, 10] et de rayon 4").
Cette classe définit également une méthode "estValide()" pour vérifier qu'une forme est valide, c'est-à-dire qu'aucune partie de la forme ne "sort" de la zone de tracé, en prenant en paramètre la zone de tracé. Une forme est "acceptée" seulement 
En plus des différents points, la classe Forme retiendra la couleur du trait (obligatoire), ainsi que la couleur de remplissage (facultatif). Si aucune couleur de remplissage n'est spécifiée, le remplissage sera omis. Les couleurs seront demandées à votre discrétion avant ou après avoir demandé à l'utilisateur les arguments de tracé.
Chaque classe enfant de Forme devra surcharger l'opérateur << afin d'afficher une description de la forme.

### 2.1.4	Classe Droite
La classe Droite, héritant de la classe Forme, permettra de demander à l'utilisateur les coordonnées nécessaires pour deux points.
Exemple de description textuelle : "Droite de couleur #FAD700 entre [0, 5] et [7, 15]".

### 2.1.5	Classe Cercle
La classe Cercle, héritant de la classe Forme, permettra de demander les coordonnées nécessaires pour le centre du cercle, ainsi qu'un rayon.
Exemple de description textuelle : "Cercle (tracé : #fad700, pas de fond) de centre [6, 6] et de rayon 4".
 
### 2.1.6	Classe Polygone
La classe Polygone, héritant de la classe Forme, permettra de demander les coordonnées nécessaires pour tracer autant de points que souhaités, qui seront reliés l'un après l'autre pour former un polygone.
Exemple de description textuelle : "Polygone (tracé : #fad700, pas de fond) de coordonnées ([1, 1], [4, 8], [3, 7])".

### 2.1.7	Classe Couleur
La classe Couleur permet de représenter une couleur sous format RGB (rouge, vert, bleu). Cette classe devra définir les méthodes suivantes :
*	toHexa() : retourne la représentation textuelle de la couleur en format héxadécimal (ex : "FAD700")
*	toString() : retourne la représentation textuelle de la couleur sous format RGB (ex : "250, 180, 55")
*	Surcharge d'opérateur << qui devra retourner la représentation textuelle sous format héxadécimal

### 2.1.8	Classe Generateur
La classe Generateur est une classe abstraite définissant la méthode "generer()" prenant en argument une zone de tracé.

### 2.1.9	Classe BMPgenerateur
La classe BMPgenerateur permet la génération d'un fichier BMP. Le nom du fichier BMP sera demandé à l'utilisateur. Attention à vérifier que le nom saisi génère un fichier dans le dossier courant. Cette classe va logiquement utiliser la librairie de génération BMP fournie en Annexe A2.
Note : il n'existe pas de transparence en BMP – on considérera la couleur de fond de la zone de tracé comme étant la couleur "transparente". Si la couleur de fond de la zone de tracé n'est pas spécifiée, on considérera du blanc.

### 2.1.10	Classe SVGgenerateur (et enfants)
La classe SVGgenerateur est une classe permettant la génération sous format SVG. C'est une classe parente de SVGgenerateurFichier et SVGgenerateurTexte. Le premier effectue une génération d'un fichier SVG. Le second effectue une génération d'une chaîne SVG qui sera affichée dans la console.
 
## 2.2	Tests
### 2.2.1	Tracé d'une ligne
Effectuez la génération d'une droite entre les coordonnées [5, 5] et [5, 10] dans une zone de tracé de 20 sur 20. Aucune couleur n'est nécessaire. Afficher, en console, la zone (avec ses formes).

### 2.2.2	Tracé de trois lignes
Effectuez la génération de trois lignes aux coordonnées ([10, 10], [10, 40]), ([10, 40], [40, 40]) et ([40, 40], [40, 10]) de couleur noir sur fond transparent. Afficher, en console, la zone (avec ses formes).

### 2.2.3	Tracé de trois lignes en SVG (texte)
Effectuez le tracé du 2.2.2 et affichez le résultat sous forme SVG.

### 2.2.4	Tracé d'un cercle noir sur blanc
Effectuez la génération d'un cercle de centre [4, 4] et de rayon 3, dans une zone de tracé de 10 sur 10. Le cercle sera noir avec un remplissage bleu. Afficher, en console, la zone (avec ses formes).

### 2.2.5	Génération d'un SVG textuel
Effectuez la génération des formes nécessaires pour tracer "LEOPOLD" sur un canvas de largeur 500 sur hauteur 200. Les lettres L seront en rouge, les lettres O seront en vert sur fond jaune, et les autres lettres seront en noir sur fond "transparent". Le résultat attendu est la génération d'un SVG textuel (donc via la classe SVGgenerateurTexte). Vous pouvez tester le SVG en l'enregistrant dans un fichier SVG manuellement sur votre bureau et en l'ouvrant dans votre navigateur.

### 2.2.6	Génération d'un SVG (fichier)
Effectuez la même génération qu'en 2.2.5, mais sous format d'un fichier SVG d'un nom choisi par l'utilisateur (donc via la classe SVGgenerateurFichier).

### 2.2.7	Génération d'un BMP (fichier)
Effectuez la même génération qu'en 2.2.5, mais sous format d'un fichier BMP d'un nom choisi par l'utilisateur (donc via la classe BMPgenerateurFichier).
