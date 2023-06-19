//
// Created by Daniel on 19-Jun-23.
//

#pragma once
#include <utility>

#include "Student.h"
#include "vector"
#include "fstream"
#include "sstream"
#include "algorithm"
#include "exception"

class IntinerireError: public exception{
private:
    string msg;
public:
    /**
     * constructor
     * @param msg string
     */
    IntinerireError(string msg): msg(std::move(msg)) {}

    /**
     * returneaza mesajul continut
     * @return rez - string
     */
    string getMsg(){
        return msg;
    }
};

class Repo{
private:
    vector<Student> studenti;
    string path;

public:
    /**
     * constructor, initializeaza si pathul spre fisier
     * @param path string
     */
    explicit Repo(string path): path(std::move(path)) {}

    /**
     * citeste datele din fisier
     */
    void read(){
        ifstream f(path);
        studenti.clear();

        string line;
        while (getline(f, line)){
            string token;
            vector<string> tmp;
            stringstream ss(line);
            while (getline(ss,token,','))
                tmp.push_back(token);

            Student student(stoi(tmp[0]), tmp[1], stoi(tmp[2]), tmp[3]);
            studenti.push_back(student);
        }
        f.close();
    }

    /**
     * scrie datele in fisier
     */
    void write(){
        ofstream g(path);

        for (auto& student : studenti){
            g << student.getId() << ',';
            g << student.getNume() << ',';
            g << student.getVarsta() << ',';
            g << student.getFacultate() << '\n';
        }
        g.close();
    }

    /**
     * returneaza studentii
     * @return rez - vector<Student>
     */
    vector<Student>& getAll(){
        read();
        return studenti;
    }

    /**
     * sterge studentul cu id ul dat
     * @param id int
     */
    void stergeStudent(int id) {
        read();
        for (int i = 0; i < studenti.size(); ++i) {
            if (studenti[i].getId() == id)
                studenti.erase(studenti.begin() + i);
        }
        write();
    }

    /**
     * intinereste cu 1 an toti studentii
     * throws IntinerireError daca minim 1 student nu poate fi intinerit
     */
    void intinerire(){
        read();
        for (auto& st : studenti){
            int varsta = st.getVarsta();
            if (varsta <= 1)
                throw IntinerireError("Nu se mai poate intineri\n");
            st.setVarsta(varsta - 1);
        }
        write();
    }

    /**
     * imbatraneste cu 1 an toti studentii
     */
    void imbatranire(){
        read();
        for (auto& st : studenti){
            int varsta = st.getVarsta();
            st.setVarsta(varsta + 1);
        }
        write();
    }

    /**
     * adauga un student in lista
     * @param st Student
     */
    void adaugaStudent(Student st){
        read();
        studenti.push_back(st);
        write();
    }

    /**
     * returneaza studentul cu id ul dat
     * @param id int
     * @return rez - Student
     */
    Student cautaStudent(int id){
        read();
        for (auto st : studenti)
            if (st.getId() == id)
                return st;
    }
};