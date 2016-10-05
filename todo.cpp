#include <QDateTime>
#include <QObject>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaEnum>

#include "todo.h"
/* this is the Todo object that will be part of the TodoPool */
Todo::Todo(const QString &title, const QString &content, const QString &todoPriority, const QString &todoType, const QDateTime &todoCreatedAt)
{
    this->setTitle(title);
    this->setContent(content);
    this->setPriority(todoPriority);
    this->setType(todoType);
    this->setCreatedAt(todoCreatedAt);
    /* updated_at = created_at by default */
    this->setUpdatedAt(todoCreatedAt);
}

Todo::~Todo()
{
}

QString Todo::title() const
{
    return this->mTitle;
}

void Todo::setTitle(const QString &title)
{
    this->mTitle = title;
}

QString Todo::content() const
{
    return this->mContent;
}

void Todo::setContent(const QString & content)
{
    this->mContent = content;
}

const QString Todo::priority() const
{
    const QMetaObject &mo = Todo::staticMetaObject;
    int index = mo.indexOfEnumerator("TodoPriority");
    QMetaEnum metaEnum = mo.enumerator(index);

    return metaEnum.valueToKey(this->mPriority);
}

void Todo::setPriority(const QString &todoPriority)
{
    const QMetaObject &mo = Todo::staticMetaObject;
    int index = mo.indexOfEnumerator("TodoPriority");
    QMetaEnum metaEnum = mo.enumerator(index);
    int value = metaEnum.keyToValue(qPrintable(todoPriority));
    mPriority = static_cast<Todo::TodoPriority>(value);
}

const QString Todo::type() const
{
    const QMetaObject &mo = Todo::staticMetaObject;
    int index = mo.indexOfEnumerator("TodoType");
    QMetaEnum metaEnum = mo.enumerator(index);

    return metaEnum.valueToKey(mType);
}

void Todo::setType(const QString &todoType)
{
    const QMetaObject &mo = Todo::staticMetaObject;
    int index = mo.indexOfEnumerator("TodoType");
    QMetaEnum metaEnum = mo.enumerator(index);
    int value = metaEnum.keyToValue(qPrintable(todoType));
    mType = static_cast<TodoType>(value);
}

QDateTime Todo::created_at() const
{
    return this->mCreatedAt;
}

void Todo::setCreatedAt(const QDateTime &datetime)
{
    this->mCreatedAt = datetime;
}

QDateTime Todo::updated_at() const
{
    return this->mCreatedAt;
}

void Todo::setUpdatedAt(const QDateTime &datetime)
{
    this->mUpdatedAt = datetime;
}


const QJsonObject &Todo::read(const QJsonObject &json)
{
    mTitle = json["title"].toString();
    mPriority = Todo::TodoPriority(qRound(json["priority"].toDouble()));
    mType = Todo::TodoType(qRound(json["type"].toDouble()));
    mContent = json["content"].toString();
    return json;
}

bool Todo::write(const QJsonObject &json)
{
    json["title"] = this->mTitle;
    json["priority"] = this->mPriority;
    json["type"] = this->mType;
    json["updated_at"] = QDateTime::currentDateTime().toString();
     return true;
}
