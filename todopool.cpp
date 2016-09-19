#include <QString>
#include <QDateTime>
#include <QObject>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaEnum>
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

bool TodoPool::saveTodoList(const QString &saveFormat) const
{
    return true;
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

bool TodoPool::comparison(const Todo &todo1, const Todo &todo2)
{
   switch(mSorting)
   {
   case Alphabetical:
       if (mOrdering == Asc)
           return todo1.title().toLower()[0] < todo2.title().toLower()[0];
       return todo1.title().toLower()[0] > todo2.title().toLower()[0];
   case CreatedAt:
       if (mOrdering == Asc)
           return todo1.created_at() < todo2.created_at();
       return todo1.created_at() > todo2.created_at();
   case UpdatedAt:
       if (mOrdering == Asc)
           return todo1.updated_at() < todo2.updated_at();
       return todo1.updated_at() < todo2.created_at();
   }
   return NULL;
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
    std::sort(this->mTodoList.begin(), this->mTodoList.end(), comparison);
}

