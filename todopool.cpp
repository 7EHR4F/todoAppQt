#include <QString>
#include <QDateTime>
#include <QObject>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaEnum>
#include <QFile>
#include <iostream>
#include <algorithm>
#include "todopool.h"

TodoPool::TodoPool(const QString &todoListSorting, const QString &todoListOrdering)
{
    TodoPool::setSorting(todoListSorting);
    TodoPool::setOrdering(todoListOrdering);
}

TodoPool::~TodoPool()
{
}

const QString TodoPool::sorting() const
{
    const QMetaObject &mo = TodoPool::staticMetaObject;
    int index = mo.indexOfEnumerator("Sorting");
    QMetaEnum metaEnum = mo.enumerator(index);

    return metaEnum.valueToKey(mSorting);
}

void TodoPool::setSorting(const QString &Sorting){
    const QMetaObject &mo = Todo::staticMetaObject;
    int index = mo.indexOfEnumerator("Sorting");
    QMetaEnum metaEnum = mo.enumerator(index);
    int value = metaEnum.keyToValue(qPrintable(Sorting));
    enum TodoPool::Sorting mSorting = static_cast<TodoPool::Sorting>(value);
}

bool TodoPool::asc_alph_comparison(const Todo &todo1, const Todo &todo2)
{
    return todo1.title().toLower()[0] < todo2.title().toLower()[0];
}

bool TodoPool::desc_alph_comparison(const Todo &todo1, const Todo &todo2)
{
    return todo1.title().toLower()[0] > todo2.title().toLower()[0];
}

bool TodoPool::asc_created_at_comparison(const Todo &todo1, const Todo &todo2)
{
    return todo1.created_at() < todo2.created_at();
}

bool TodoPool::desc_created_at_comparison(const Todo &todo1, const Todo &todo2)
{
    return todo1.created_at() > todo2.created_at();
}

bool TodoPool::asc_updated_at_comparison(const Todo &todo1, const Todo &todo2)
{
    return todo1.updated_at() < todo2.updated_at();
}

bool TodoPool::desc_updated_at_comparison(const Todo &todo1, const Todo &todo2)
{
    return todo1.updated_at() > todo2.updated_at();
}

const QString TodoPool::ordering() const
{
    const QMetaObject &mo = TodoPool::staticMetaObject;
    int index = mo.indexOfEnumerator("Ordering");
    QMetaEnum metaEnum = mo.enumerator(index);
    return metaEnum.valueToKey(mOrdering);
}

void TodoPool::setOrdering(const QString &todoListOrdering)
{
    const QMetaObject &mo = Todo::staticMetaObject;
    int index = mo.indexOfEnumerator("Ordering");
    QMetaEnum metaEnum = mo.enumerator(index);
    int value = metaEnum.keyToValue(qPrintable(todoListOrdering));
    enum TodoPool::Ordering mOrdering = static_cast<TodoPool::Ordering>(value);
}

const QList<Todo> &TodoPool::todos() const
{
    return this->mTodoList;
}

void TodoPool::setTodoList(const QList<Todo> &todos){
    this->mTodoList = todos;
    switch(mSorting)
    {
    case Alphabetical:
        if (mOrdering == Asc)
            std::sort(this->mTodoList.begin(), this->mTodoList.end(), asc_alph_comparison);
        std::sort(this->mTodoList.begin(), this->mTodoList.end(), desc_alph_comparison);
    case CreatedAt:
        if (mOrdering == Asc)
            std::sort(this->mTodoList.begin(), this->mTodoList.end(), asc_created_at_comparison);
        std::sort(this->mTodoList.begin(), this->mTodoList.end(), desc_created_at_comparison);
    case UpdatedAt:
        if (mOrdering == Asc)
            std::sort(this->mTodoList.begin(), this->mTodoList.end(), asc_updated_at_comparison);
        std::sort(this->mTodoList.begin(), this->mTodoList.end(), desc_updated_at_comparison);
    }
}

bool TodoPool::loadTodoList(const TodoPool::SaveFormat &saveFormat)
{
    QFile loadFile(saveFormat == Json
        ? QStringLiteral("save.json")
        : QStringLiteral("save.dat"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(saveFormat == Json
        ? QJsonDocument::fromJson(saveData)
        : QJsonDocument::fromBinaryData(saveData));

    read(loadDoc.object());

    return true;
}

bool TodoPool::saveTodoList(const TodoPool::SaveFormat &saveFormat)
{
    QFile saveFile(saveFormat == Json
            ? QStringLiteral("save.json")
            : QStringLiteral("save.dat"));

        if (!saveFile.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
            return false;
        }

        QJsonObject todoListObject;
        write(todoListObject);
        QJsonDocument saveDoc(todoListObject);
        saveFile.write(saveFormat == Json
            ? saveDoc.toJson()
            : saveDoc.toBinaryData());

        return true;
}

bool TodoPool::write(const QJsonObject &json)
{
    QList<Todo>::iterator i;
    for (i = mTodoList.begin(); i != mTodoList.end(); ++i)
        i->write(json["todo"].toObject());
    return(true);
}

bool TodoPool::read(const QJsonObject &json)
{
    QList<Todo>::iterator i;
    for (i = mTodoList.begin(); i != mTodoList.end(); ++i)
        i->read(json["todo"].toObject());
    return(true);
}
