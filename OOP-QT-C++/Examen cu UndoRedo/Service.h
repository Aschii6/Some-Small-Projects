//
// Created by Daniel on 19-Jun-23.
//

#pragma once
#include <utility>

#include "Repo.h"
#include "Undo.h"

class UndoRedoError: public exception{
private:
    string msg;
public:
    explicit UndoRedoError(string msg): msg(std::move(msg)) {}

    string getMsg(){
        return msg;
    }
};

class Service{
    Repo& repo;
    vector<ActiuneUndo*> undoList;
    vector<ActiuneUndo*> redoList;
public:
    /**
     * constructor
     * @param repo Repo
     */
    explicit Service(Repo& repo): repo(repo) {}

    /**
     * returneaza toti studentii
     * @return rez - vector<Student>
     */
    vector<Student>& getAll(){
        return repo.getAll();
    }

    /**
     * intinereste toti studentii
     */
    void intinerire(){
        repo.intinerire();

        if (!redoList.empty()){
            for (auto& act : redoList){
                delete act;
            }
            redoList.clear();

            for (auto& act : undoList){
                delete act;
            }
            undoList.clear();
        }

        undoList.push_back(new UndoIntinerire(repo));
    }

    /**
     * imbatraneste toti studentii
     */
    void imbatranire(){
        repo.imbatranire();


        if (!redoList.empty()){
            for (auto& act : redoList){
                delete act;
            }
            redoList.clear();

            for (auto& act : undoList){
                delete act;
            }
            undoList.clear();
        }
        undoList.push_back(new UndoImbatranire(repo));
    }

    /**
     * sterge studentul cu id ul dat
     * @param id int
     */
    void stergeStudent(int id){
        Student st = repo.cautaStudent(id);
        repo.stergeStudent(id);

        if (!redoList.empty()){
            for (auto& act : redoList){
                delete act;
            }
            redoList.clear();

            for (auto& act : undoList){
                delete act;
            }
            undoList.clear();
        }

        undoList.push_back(new UndoSterge(repo, st));
    }

    /**
     * aduaga studentul dat
     * @param st Student
     */
    void adaugaStudent(Student st){
        repo.adaugaStudent(st);

        if (!redoList.empty()){
            for (auto& act : redoList){
                delete act;
            }
            redoList.clear();

            for (auto& act : undoList){
                delete act;
            }
            undoList.clear();
        }

        undoList.push_back(new UndoAdauga(repo, st));
    }

    /**
     * undo
     */
    void undo(){
        if (undoList.empty())
            throw UndoRedoError("Nu se mai poate face undo");

        ActiuneUndo* act = undoList.back();

        undoList.pop_back();
        act->doUndo();

        redoList.push_back(act);
    }

    /**
     * redo
     */
    void redo(){
        if (redoList.empty())
            throw UndoRedoError("Nu se mai poate face redo");

        ActiuneUndo* act = redoList.back();
        redoList.pop_back();
        act->doRedo();

        undoList.push_back(act);
    }
};
