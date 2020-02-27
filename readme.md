# Compilation Avancée - Projet Machine Universelle
### Auteur : 
``` WANG Ruiwen ```

``` Ce projet sert à réaliser une machine universelle pour décoder les fichiers bytecode et modéliser comment elle fonctionne avec des instrcutions spécifiques.  ```
 

## Getting Started 
* les dossier : 
* src contient le code source de la machine universelle
* bin contient les buildfile
* data contient les fichiers bytecode à traiter
* output contient les résultat renvoie par la machine 

### Prerequisites
projet est codé en C,donc : 
```gcc```

### Installation 
* pour compiler le projet:
    ```make```

### Usage example 
*   pour exécuter le projet tester en sandmark et codex:
    ```make run```
    * pour exécuter le projet tester en cmu.um:
    ```make testUm```    
    * pour voir le résultat exécuter avec sandmark:
    ```make checkSandmark```
    * pour voir le résultat exécuter avec codex:
    ```make checkCodex```
    * pour voir le résultat exécuter avec cmu.um:
    ```make checkUm```



## Release History 

* 0.1.0 - réaliser tous les fonctions mais la machine s'arrèt au boucle 387 avec div error

## Data Structure 
* plateau : int 
* tab_plateaux : unsigned int**
* registre : int[8]

## Problème reste:
* Je ne sais pas pourquoi au boucle 387 la machine lance 'div error' mais j'ai éssayé plusieur fois pour tester les fonction ceux sont bien marcher
