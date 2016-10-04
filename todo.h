#ifndef TODO_H
#define TODO_H
#include <QDateTime>
#include <QCoreApplication>
#include <QString>
#include <QJsonDocument>

class Todo
{

    Q_GADGET
    Q_ENUMS(TodoType)
    Q_ENUMS(TodoPriority)
public:

    enum TodoType {
        Text, Audio, Video
    };

    enum TodoPriority {
        High, Medium, Low
    };

    Todo();
    Todo(const QString &title = "", const QString &content = "", const QString &todoPriority = "Medium", const QString &todoType = "Text", const QDateTime &todoCreatedAt = QDateTime::currentDateTime());
    ~Todo();

    QString title() const;
    void setTitle(const QString &title);

    QString content() const;
    void setContent(const QString &content);
    const QString priority() const;
    void setPriority(const QString &TodoPriority);

    const QString type() const;
    void setType(const QString &todoType);

    QDateTime created_at() const;
    void setCreatedAt(const QDateTime &datetime);

    QDateTime updated_at() const;
    void setUpdatedAt(const QDateTime &datetime);

    const QJsonObject &read(const QJsonObject &json);
    bool write(const QJsonObject &json);

private:
    QString mTitle;
    enum TodoType mType;
    enum TodoPriority mPriority;
    QString mContent;
    QDateTime mCreatedAt;
    QDateTime mUpdatedAt;
};


#endif // TODO_H
