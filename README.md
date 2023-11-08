# Blockchain-module-practice
Vilnius University study module practice files
# Antra versija
### Antros versijos pridėtinės funkcijos:

- Vietoje visų transakcijų hash'o bloke dabar naudojamas saugesnis **merkle root hash**, o merkle medis sudaromas iš visų bloke esančių transakcijų. Tuo tikslu sukurtas _struct HashPointer_ ir atnaujinta _class Block_ member funkcija set_merkle()
- Prieš dedant transakcijas į baseiną, patikrinama, ar siuntėjas turi pakankamai lėšų išsiųsti sumą _amount._ Jei ne, transakcija atmetama
- Blokų kasimo procesas patobulintas: dabar jei kasamas blokas užtrunka ilgiau nei 5 sekundes, bandomas kitas kandidatas
- Naudojamas geresnis hash algoritmas (kursiokės Lauritos)

### Failai

- _main.h_ aprašo pagrindines tris klases: _class User, class Transaction, class Block_. Kiekviena klasė turi išsamiai aprašytas member funkcijas. Taip pat čia deklaruojamos visos kitos funkcijos ir įtrauktos bibliotekos.
- _functions.cpp_ arprašo kai kurias _friend_ funkcijas bei pagrindinę _hash_ funkciją
- _main.cpp_ pagrindinis failas, aprašoma programos eiga.

**Naudojimas:** programa paleidžiama automatiškai vykdo blokų generavimą ir skaičiavimus. Ekrane išvedami blokai, o jei procese atsirado trikdžių, tai irgi pranešama vartotojui. Programa sustoja automatiškai.

# Pirma versija
