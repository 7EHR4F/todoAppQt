#ifndef TODOPOOL_H
#define TODOPOOL_H
#include <QList>
#include "todo.h"

class TodoPool : public QObject
{

    Q_OBJECT
    Q_ENUMS(Sorting)
    Q_ENUMS(Ordering)
    Q_ENUMS(SaveFormat)

public:
    TodoPool();
    TodoPool(const QString &todoListSorting, const QString &todoListOrdering);
    ~TodoPool();
    enum Sorting {
            CreatedAt, UpdatedAt, Alphabetical
    };

    enum Ordering {
            Asc, Desc
    };

    enum SaveFormat {
            Json, Binary
    };

private:
    const QString sorting() const;
    void setSorting(const QString &todoListSorting);
    const QString ordering() const;
    void setOrdering(const QString &todoListOrdering);
    const QList<Todo> &todos() const;
    void setTodoList(const QList<Todo> &todos);
    const QJsonObject &read(const QJsonObject &json);
    const QJsonObject &write(const QJsonObject &json);
    bool loadTodoList(const SaveFormat  &saveFormat);
    bool saveTodoList(const SaveFormat &saveFormat);
    static bool asc_alph_comparison(const Todo &todo1, const Todo &todo2);
    static bool desc_alph_comparison(const Todo &todo1, const Todo &todo2);
    static bool asc_created_at_comparison(const Todo &todo1, const Todo &todo2);
    static bool desc_created_at_comparison(const Todo &todo1, const Todo &todo2);
    static bool asc_updated_at_comparison(const Todo &todo1, const Todo &todo2);
    static bool desc_updated_at_comparison(const Todo &todo1, const Todo &todo2);
    QList<Todo> mTodoList;
    enum Ordering mOrdering;
    enum Sorting mSorting;
    enum SaveFormat mSaveFormat;
};

#endif // TODOPOOL_H
