divert(-1)

define(LOG_INFO, Log.info("`__FILENAME__'", `__line__', $1))
define(LOG_DEBUG, Log.debug("`__FILENAME__'", `__line__', $1))
define(LOG_ERROR, Log.error("`__FILENAME__'", `__line__', $1))

divert(0)