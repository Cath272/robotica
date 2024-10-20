LAB 1:
Am inceput prin a crea schema electrica in wowki:
Componente utilizate:

 - 4 led-uri albastre
 - 1 led RGB cu anod comun 
 - 7 rezistente de 220Ohm
 - 2 rezistente de 1K
 - 2 butoane 
 - Placa Arduino Uno
![image](https://github.com/user-attachments/assets/db5d4e7b-b39c-45a2-b35d-7c763405db53)

Dupa tot in wowki am creat codul, acesta foloseste 2 butoane cu debounce, cand butonul 1 este apasat iar starea este libera (becul este verde) incepe incarcarea prin schimbarea starii primului led de 6 ori, schimband din on in off la 0,5s, apoi trecand prin fiecare led ce urmeaza. Daca butonul de reset este apasat timp de 1s, acesta reseteaza starea de incarcare si apeleaza functia chargingStop() ce face blink la toate 4 led-urile si apoi trece starea inpoi in liber.
Codul se poate gasi in main.cpp
Dupa am facut setup-ul fizic:
![20241016_185916](https://github.com/user-attachments/assets/b4c19613-d6a1-4a48-bb50-2efdadf6ab64)

Iar la final am incarcat codul pe placa:

https://s.go.ro/bac3ug6s
[Link aici]([https://link-url-here.org](https://s.go.ro/bac3ug6s))

