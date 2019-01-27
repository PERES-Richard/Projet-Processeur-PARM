# Projet PARM 2018 - Équipe gens-bon-2

## Membres
- Thomas COLLOMBAN
- Alexis LEFEBVRE
- Alexandre LONGORDO
- Richard PERES

## Contenu de l'archive
Cette archive contient l'ensemble des circuits logisims réalisés, du code C utilisé pour le parsage/compilage du code assembleur ainsi que le diaporama utilisé lors de la présentation.

## Index
###  ALU.circ :
        Circuit Logisim de l'ALU (avec test)
###  BancDeRegistre.circ :
        Circuit Logisim du BancDeRegistre
###  controller.circ :
        Circuit Logisim de du Controller (avec test)
###  Machine.circ :
        Circuit Logisim de donné en annexe du projet
###  logisim-generic-2.7.1.jar :
        Version de Logisim utilisée pour réalisé les circuit
###  Diapo_PARM_gens-bons-2.pdf :
        Diaporama utilisé lors de la soutenance

###  complier 2019/main.exe :
        Executable du compilateur assembleur/bianire (cf. section _Utilisation_)
###  complier 2019/test.exe :
        Executable des tests du compilateur (cf. section _Utilisation_)
###  complier 2019/Makefile :
        Makefile utilisé pour compiler le programme C (cf. section _Utilisation_)
###  complier 2019/asm.c :
        Partie du code où le parsage et la compilation en binaire se fait
###  complier 2019/main.c :
        Main du programme qui va grossièrement initialiser l'environnement et utilisé asm.c pour effectuer la compilation en binaire
###  complier 2019/test.c :
        Fichier où sont effectués les test en comparant le résultat attendu à une suite d'instructions et le resutat observé avec notre programme
###  complier 2019/code_test2.asm :
        Fichier assembleur contenant en 1 exemplaire toute les instructions
###  complier 2019/code_test2.asm :
        Fichier assembleur contenant des instructions de conditions et variables (code présent sur le Forum Assmebleur)
###  complier 2019/*c et *h :
        Le reste du code C.


## Utilisation
### main.exe :
        main.exe code_assembleur.asm [fichier_output.out (a.out si non renseigné)]

        Par exemple :
            main.exe code_test2.asm
            ou encore
            main.exe code_testB.asm binaire.out
### test.exe
        Aucun argument nécessaire. L'executable va lancer le programme de test dans test.c et affiché le résultat.
### Makefile
        make ==> Généré l'executable "main.exe"
        make test ==> Généré l'executable "test.exe"
        make clean ==> Supprimer tous les .o
