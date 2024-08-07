#ifndef MACROS_H
#define MACROS_H

#define AUTO_PROPERTY(TYPE, NAME)                                         \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME##Changed FINAL) \
public:                                                                   \
    TYPE NAME() const                                                     \
    {                                                                     \
        return m_##NAME;                                                  \
    }                                                                     \
    void NAME(const TYPE& newValue)                                       \
    {                                                                     \
        if (m_##NAME != newValue) {                                       \
            m_##NAME = newValue;                                          \
            emit NAME##Changed(newValue);                                 \
        }                                                                 \
    }                                                                     \
signals:                                                                  \
    Q_SIGNAL void NAME##Changed(const TYPE& newValue);                    \
                                                                          \
private:                                                                  \
    TYPE m_##NAME;

#define AUTO_PROPERTY_DEFAULT(TYPE, NAME, DEFAULT)                        \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME##Changed FINAL) \
public:                                                                   \
    TYPE NAME() const                                                     \
    {                                                                     \
        return m_##NAME;                                                  \
    }                                                                     \
    void NAME(const TYPE& newValue)                                       \
    {                                                                     \
        if (m_##NAME != newValue) {                                       \
            m_##NAME = newValue;                                          \
            emit NAME##Changed(newValue);                                 \
        }                                                                 \
    }                                                                     \
signals:                                                                  \
    Q_SIGNAL void NAME##Changed(const TYPE& newValue);                    \
                                                                          \
private:                                                                  \
    TYPE m_##NAME = DEFAULT;

#define AUTO_PROPERTY_WRITE_DEFAULT(TYPE, NAME, DEFAULT)                  \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME##Changed FINAL) \
public:                                                                   \
    TYPE NAME() const                                                     \
    {                                                                     \
        return m_##NAME;                                                  \
    }                                                                     \
    \
signals:                                                                  \
    Q_SIGNAL void NAME##Changed(const TYPE& newValue);                    \
                                                                          \
private:                                                                  \
    TYPE m_##NAME = DEFAULT;

#endif // MACROS_H
