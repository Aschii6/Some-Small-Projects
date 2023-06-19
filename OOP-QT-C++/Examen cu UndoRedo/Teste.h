//
// Created by Daniel on 19-Jun-23.
//

#pragma once
#include "Student.h"
#include "Repo.h"
#include "Service.h"
#include "cassert"

void testeStudent(){
    int id = 20;
    string nume = "Adrian";
    int varsta = 18;
    string facultate = "info";

    Student student(id, nume, varsta, facultate);

    assert(student.getId() == id);
    assert(student.getVarsta() == varsta);
    assert(student.getNume() == nume);
    assert(student.getFacultate() == facultate);

    student.setVarsta(20);
    assert(student.getVarsta() == 20);
}

void testeRepoService(){
    Repo repo("teste.txt");
    Service service(repo);

    vector<Student> studenti = service.getAll();

    assert(studenti.size() == 3);

    assert(studenti[0].getId() == 10);
    assert(studenti[1].getId() == 13);
    assert(studenti[2].getId() == 22);

    Student stCopie = studenti[2];

    service.stergeStudent(22);

    assert(service.getAll().size() == 2);

    service.adaugaStudent(stCopie);

    assert(service.getAll().size() == 3);

    assert(service.getAll()[0].getVarsta() == 18);
    service.imbatranire();
    assert(service.getAll()[0].getVarsta() == 19);
    service.intinerire();
    assert(service.getAll()[0].getVarsta() == 18);
}

void allTeste(){
    testeStudent();
    testeRepoService();
}
