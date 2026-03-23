
    Programul gestioneaza evidenta studentilor, a disciplinelor si a notelor obtinute de studenti.

    Date de intrare:
    - fisierul "studenti.txt", care contine pentru fiecare student:
      id, nume, grupa
    - fisierul "discipline.txt", care contine pentru fiecare disciplina:
      cod, denumire, numar de credite
    - fisierul "note.txt", care contine pentru fiecare nota:
      id student, cod disciplina, valoarea notei

    Pe baza acestor date, utilizatorul poate vizualiza lista studentilor
    si a disciplinelor, poate analiza situatia scolara a unui student,
    poate calcula mediile (simpla si ponderata in functie de credite)
    si poate identifica studenti integralisti sau restantieri.

    In plus, programul permite adaugarea de noi studenti, discipline
    si note, precum si actualizarea unei note existente daca aceasta
    este reintrodusa.

    La final, se determina si se afiseaza seful de promotie,
    adica studentul cu cea mai mare medie ponderata.

    Clase folosite:
    - Student
    - Disciplina
    - Nota
    - Catalog
