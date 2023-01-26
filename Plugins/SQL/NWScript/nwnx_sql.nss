/// @addtogroup sql SQL
/// @brief Functions to interface with a database through SQL
/// @{
/// @file nwnx_sql.nss
#include "nwnx"

const string NWNX_SQL = "NWNX_SQL"; ///< @private

/// @brief Prepares the provided query for execution.
/// @note This does not execute the query. Will also clear any previous state.
/// @param query The query to prepare.
/// @return TRUE if the query was successfully prepared.
int NWNX_SQL_PrepareQuery(string query);

/// @brief Executes a query which has been prepared.
/// @return The ID of this query if successful, else FALSE.
int NWNX_SQL_ExecutePreparedQuery();

/// @brief Directly execute an SQL query.
/// @note Clears previously prepared query states.
/// @return The ID of this query if successful, else FALSE.
int NWNX_SQL_ExecuteQuery(string query);

/// @anchor sql_rtrnr
/// @return TRUE if one or more rows are ready, FALSE otherwise.
int NWNX_SQL_ReadyToReadNextRow();

/// @anchor sql_rnr
/// @brief Reads the next row of returned data.
/// @remark Should only be called after a successful call to @ref sql_rtrnr "NWNX_SQL_ReadyToReadNextRow()".
void NWNX_SQL_ReadNextRow();

/// @param column The column to read in the active row.
/// @return Data at the nth (0-based) column of the active row.
/// @remark Should only be called after a successful call to @ref sql_rnr "NWNX_SQL_ReadNextRow()".
string NWNX_SQL_ReadDataInActiveRow(int column = 0);

/// @brief Set the int value of a prepared statement at given position.
/// @param position The nth ? in a prepared statement.
/// @param value The value to set.
void NWNX_SQL_PreparedInt(int position, int value);

/// @brief Set the string value of a prepared statement at given position.
/// @param position The nth ? in a prepared statement.
/// @param value The value to set.
void NWNX_SQL_PreparedString(int position, string value);

/// @brief Set the float value of a prepared statement at given position.
/// @param position The nth ? in a prepared statement.
/// @param value The value to set.
void NWNX_SQL_PreparedFloat(int position, float value);

/// @brief Set the ObjectId value of a prepared statement at given position.
/// @param position The nth ? in a prepared statement.
/// @param value The value to set.
void NWNX_SQL_PreparedObjectId(int position, object value);

/// @brief Set the full serialized object value of a prepared statement at given position.
/// @param position The nth ? in a prepared statement.
/// @param value The value to set.
/// @param base64 Use base64-encoded string format if TRUE (default), otherwise use binary format.
void NWNX_SQL_PreparedObjectFull(int position, object value, int base64 = TRUE);

/// @brief Set the NULL value of a prepared statement at given position.
/// @param position The nth ? in a prepared statement.
void NWNX_SQL_PreparedNULL(int position);

/// @brief Like NWNX_SQL_ReadDataInActiveRow, but for full serialized objects.
///
/// The object will be deserialized and created in the game. New object ID is returned.
///
/// The exact behavior depends on type of deserialized object and owner object:
///   * If object is an item, and owner if placeable, creature or container, the item will be created in its inventory
///   * If owner is an area, the object will be created on the ground at Vector(x,y,z)
///   * Otherwise, the object will be created outside the world and needs to be ported manually.
///
/// @param column The column to read in the active row.
/// @param owner The owner of the object.
/// @param x, y, z The vector for objects to be placed in areas.
/// @param base64 Use base64-encoded string format if TRUE (default), otherwise use binary format.
/// @return The deserialized object.
object NWNX_SQL_ReadFullObjectInActiveRow(int column = 0, object owner = OBJECT_INVALID, float x = 0.0, float y = 0.0, float z = 0.0, int base64 = TRUE);

/// @brief Gets the rows affected by a query.
/// @remark This command is for non-row-based statements like INSERT, UPDATE, DELETE, etc.
/// @return Number of rows affected by SQL statement or -1 if the query was not non-row-based.
int NWNX_SQL_GetAffectedRows();

/// Gets the database type.
/// @return The database type we're interacting with.
/// @remark This is the same value as the value of NWNX_SQL_TYPE environment variable.
string NWNX_SQL_GetDatabaseType();

/// @brief Free any resources attached to an existing prepared query.
/// @remark Resources are automatically freed when a new query is prepared, so calling this isn't necessary.
void NWNX_SQL_DestroyPreparedQuery();

/// @return The last error message generated by the database.
string NWNX_SQL_GetLastError();

/// @brief Gets the number of parameteres expected by a prepared query.
/// @return Returns the number of parameters expected by the prepared query or -1 if no query is prepared.
int NWNX_SQL_GetPreparedQueryParamCount();

/// @brief Set the next query to return full binary results **ON THE FIRST COLUMN ONLY**.
/// @note This is ONLY needed on PostgreSQL, and ONLY if you want to deserialize raw bytea in NWNX_SQL_ReadFullObjectInActiveRow with base64=FALSE.
void NWNX_SQL_PostgreSQL_SetNextQueryResultsBinaryMode();

/// @}

int NWNX_SQL_PrepareQuery(string query)
{
    string sFunc = "PrepareQuery";

    NWNX_PushArgumentString(query);
    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueInt();
}

int NWNX_SQL_ExecutePreparedQuery()
{
    string sFunc = "ExecutePreparedQuery";

    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueInt();
}

int NWNX_SQL_ExecuteQuery(string query)
{
    // Note: the implementation might change as support for more SQL targets arrives.
    if (NWNX_SQL_PrepareQuery(query))
    {
        int ret = NWNX_SQL_ExecutePreparedQuery();
        NWNX_SQL_DestroyPreparedQuery();
        return ret;
    }

    return FALSE;
}

int NWNX_SQL_ReadyToReadNextRow()
{
    string sFunc = "ReadyToReadNextRow";

    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueInt();
}

void NWNX_SQL_ReadNextRow()
{
    string sFunc = "ReadNextRow";

    NWNX_CallFunction(NWNX_SQL, sFunc);
}

string NWNX_SQL_ReadDataInActiveRow(int column = 0)
{
    string sFunc = "ReadDataInActiveRow";

    NWNX_PushArgumentInt(column);
    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueString();
}


void NWNX_SQL_PreparedInt(int position, int value)
{
    string sFunc = "PreparedInt";

    NWNX_PushArgumentInt(value);
    NWNX_PushArgumentInt(position);
    NWNX_CallFunction(NWNX_SQL, sFunc);
}
void NWNX_SQL_PreparedString(int position, string value)
{
    string sFunc = "PreparedString";

    NWNX_PushArgumentString(value);
    NWNX_PushArgumentInt(position);
    NWNX_CallFunction(NWNX_SQL, sFunc);
}
void NWNX_SQL_PreparedFloat(int position, float value)
{
    string sFunc = "PreparedFloat";

    NWNX_PushArgumentFloat(value);
    NWNX_PushArgumentInt(position);
    NWNX_CallFunction(NWNX_SQL, sFunc);
}
void NWNX_SQL_PreparedObjectId(int position, object value)
{
    string sFunc = "PreparedObjectId";

    NWNX_PushArgumentObject(value);
    NWNX_PushArgumentInt(position);
    NWNX_CallFunction(NWNX_SQL, sFunc);
}
void NWNX_SQL_PreparedObjectFull(int position, object value, int base64 = TRUE)
{
    string sFunc = "PreparedObjectFull";

    NWNX_PushArgumentInt(base64);
    NWNX_PushArgumentObject(value);
    NWNX_PushArgumentInt(position);
    NWNX_CallFunction(NWNX_SQL, sFunc);
}
void NWNX_SQL_PreparedNULL(int position)
{
    string sFunc = "PreparedNULL";

    NWNX_PushArgumentInt(position);
    NWNX_CallFunction(NWNX_SQL, sFunc);
}


object NWNX_SQL_ReadFullObjectInActiveRow(int column = 0, object owner = OBJECT_INVALID, float x = 0.0, float y = 0.0, float z = 0.0, int base64 = TRUE)
{
    string sFunc = "ReadFullObjectInActiveRow";

    NWNX_PushArgumentInt(base64);
    NWNX_PushArgumentFloat(z);
    NWNX_PushArgumentFloat(y);
    NWNX_PushArgumentFloat(x);
    NWNX_PushArgumentObject(owner);
    NWNX_PushArgumentInt(column);
    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueObject();
}

int NWNX_SQL_GetAffectedRows()
{
    string sFunc = "GetAffectedRows";

    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueInt();
}

string NWNX_SQL_GetDatabaseType()
{
    string sFunc = "GetDatabaseType";

    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueString();
}

void NWNX_SQL_DestroyPreparedQuery()
{
    string sFunc = "DestroyPreparedQuery";

    NWNX_CallFunction(NWNX_SQL, sFunc);
}

string NWNX_SQL_GetLastError()
{
    string sFunc = "GetLastError";

    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueString();
}

int NWNX_SQL_GetPreparedQueryParamCount()
{
    string sFunc = "GetPreparedQueryParamCount";

    NWNX_CallFunction(NWNX_SQL, sFunc);
    return NWNX_GetReturnValueInt();
}

void NWNX_SQL_PostgreSQL_SetNextQueryResultsBinaryMode()
{
    string sFunc = "PostgreSQL_SetNextQueryResultsBinaryMode";

    NWNX_CallFunction(NWNX_SQL, sFunc);
}
