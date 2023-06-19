//
// Created by Daniel on 19-Jun-23.
//

#pragma once
#include <utility>

/**
 * Clasa abstracta ActiuneUndo, are operatie de undo si de redo
 */
class ActiuneUndo{
public:
    virtual void doUndo() = 0;
    virtual void doRedo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga: public ActiuneUndo{
private:
    Student st;
    Repo& repo;
public:
    UndoAdauga(Repo& repo, Student st): repo(repo), st(st) {}

    void doUndo() override{
        repo.stergeStudent(st.getId());
    }

    void doRedo() override{
        repo.adaugaStudent(st);
    }
};

class UndoSterge: public ActiuneUndo{
private:
    Student st;
    Repo& repo;
public:
    UndoSterge(Repo& repo, Student st): repo(repo), st(st) {}

    void doUndo() override{
        repo.adaugaStudent(st);
    }

    void doRedo() override{
        repo.stergeStudent(st.getId());
    }
};

class UndoIntinerire: public ActiuneUndo{
private:
    Repo& repo;
public:
    UndoIntinerire(Repo& repo): repo(repo) {}

    void doUndo() override{
        repo.imbatranire();
    }

    void doRedo() override{
        repo.intinerire();
    }
};

class UndoImbatranire: public ActiuneUndo{
private:
    Repo& repo;
public:
    UndoImbatranire(Repo& repo): repo(repo) {}

    void doUndo() override{
        repo.intinerire();
    }

    void doRedo() override{
        repo.imbatranire();
    }
};