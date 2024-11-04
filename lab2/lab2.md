Tema 2: Am inceput prin a crea schema electrica in wowki: Componente utilizate:

   
  1 led RGB cu anod comun
  3 rezistente de 220Ohm
  2 rezistente de 1K
  2 butoane
  Placa Arduino Uno 

  ![image](https://github.com/user-attachments/assets/4728286e-088b-46a2-8a8f-208aad9ea76d)

  Dupa am facut setup-ul fizic:

  
![20241104_204444](https://github.com/user-attachments/assets/ad18d855-4b7a-483c-a0bd-f1eb8b5fc890)


Dupa am inceput sa scriu codul pentru placa: Acesta se foloseste de un button cu interrupt pentru dificultate si alt buton pentru start/stop joc. Dupa in terminal se afiseaza random cuvinte dintr-un vector des string care se tasteaza in terminal litera cu litera si se verifica fata de cuvantul dat. Daca este corect se adauga un punct la joc si trece la un nou cuvant, daca trec mai multe secunde trece automat la alt cuvant. Jocul se termina dupa 30s si afiseaza scorul final.

Video:
https://s.go.ro/54l1db63
