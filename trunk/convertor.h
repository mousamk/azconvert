/*!
 * @file convertor.h
 * @brief This files contains declaration of Convertor class.
 *
 * @author Mousa Moradi
 */

#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <QObject>


class QProgressDialog;

/*!
 * @class Convertor
 * @brief This class is the base class of convertor classes, specifies their interface,
 *  and implements common features.
 */
class Convertor : public QObject
{
    Q_OBJECT
    
    
public:
    /*!
     * @brief Class constructor
     * @param parent Parent for the new object to be created
     */
    Convertor(QObject* parent);
    
    /*!
     * @brief Converts the previously set original text and returns the result.
     * @param progressDialog The progressDialog to update it while converting
     * @return The converted result
     */
    //TODO: Eliminate the parameter and setup a better synchronization system.
    virtual QString convert(QProgressDialog* progressDialog) = 0;
    
    /*!
     * @brief Reloads the dictionaries.
     */
    //TODO: A better name or mechanism.
    virtual void openDicts() = 0;
    
    /*!
     * @brief Sets the original text to be used later in converting.
     * @param text The orginial text to be converted later
     */
    virtual void setOriginalText(const QString& text) {strSource = text;}
    
    /*!
     * @brief Returns layout direction of the source script to be used in window.
     * @return The layout direction for the source script
     */
    virtual Qt::LayoutDirection getSourceLayoutDirection() = 0;
    
    /*!
     * @brief Returns layout direction of the destination script to be used in window.
     * @return The layout direction for the destination script
     */
    virtual Qt::LayoutDirection getDestinationLayoutDirection() = 0;
    
    
protected:
    /// @brief The original source text to be converted
    QString strSource;
};

#endif // CONVERTOR_H
