/**
   This file contains verious default values which are compiled into
   the enkf executable. Everytime you add something here you should
   ask yourself:

    * Can we determine this automagically.
    * Should the user be required to enter this information.

*/

#ifndef ERT_ENKF_DEFAULT
#define ERT_ENKF_DEFAULT
#include <stdbool.h>

#define DEFAULT_LOG_FILE     "log.txt"

#define DEFAULT_RUNPATH_KEY  "DEFAULT_RUNPATH"


/**
   The format string used when creating "search-strings" which should
   be replaced in the gen_kw template files - MUST contain one %s
   placeholder which will be replaced with the parameter name.
*/
#define DEFAULT_GEN_KW_TAG_FORMAT    "<%s>"


/**
  Default file name for export file for GEN_KW parameters
*/
#ifdef   __cplusplus
extern "C" {
#endif
#define DEFAULT_GEN_KW_EXPORT_NAME   "parameters"


const char * enkf_defaults_get_default_gen_kw_export_name();

#ifdef   __cplusplus
}
#endif
/**
   The format string used when creating search strings from user input
   with the 'DATA_KW' keyword. The format string must contain one '%s'
   placeholder which will be replaced with the user supplied key; can
   be just '%s' which means no ERT induced transformations.

      Example:
      -------
      DATA_KW   KEY1   VALUE1

      DATA_KW_FORMAT = [<%s>]

   In this case all occurences of '[<KEY1>]' will be replaced with
   'VALUE1'. The DATA_KW_TAG_FORMAT used on user supplied tag keys can
   in principle be different from the internal format, but this can of
   course be confusing. The internal format is hard linked to job
   description files, and can not easily be changed.
*/

//#define DEFAULT_DATA_KW_TAG_FORMAT    "<%s>"


/**
   This is the format used for tagging the internal variables like
   IENS, and ECLBASE. These values are written into the various job
   description files, care should therefor be taken before changing
   the value of this variable. It is not user modifiable, and can only
   be changed by recompiling.

*/
#define INTERNAL_DATA_KW_TAG_FORMAT   "<%s>"


/**
    The default number of block_fs instances allocated.
*/
#define ENKF_DEFAULT_NUM_BLOCK_FS_DRIVERS 32


/* Eclipse IO  related stuff */
#define DEFAULT_FORMATTED   false
#define DEFAULT_UNIFIED     false



/*
   Where the history is coming from - default value for config item:
   HISTORY_SOURCE Observe that the function:
   model_config_set_history_source() does currently not handle a
   default value different from SCHEDULE.
*/
#define DEFAULT_HISTORY_SOURCE  REFCASE_HISTORY


#define DEFAULT_MAX_SUBMIT           2        /* The number of times to resubmit - default value for config item: MAX_SUBMIT */
#define DEFAULT_MAX_INTERNAL_SUBMIT  1        /** Attached to keyword : MAX_RETRY */




/*
   Defaults for the EnKF analysis. The analysis_config object is
   instantiated with these values.
*/
#define DEFAULT_NCOMP                      1
#define DEFAULT_ENKF_TRUNCATION            0.99
#define DEFAULT_ENKF_ALPHA                 3.0
#define DEFAULT_ENKF_STD_CUTOFF            1e-6
#define DEFAULT_MERGE_OBSERVATIONS         false
#define DEFAULT_RERUN                      false
#define DEFAULT_RERUN_START                0
#define DEFAULT_UPDATE_LOG_PATH            "update_log"
#define DEFAULT_SINGLE_NODE_UPDATE         false
#define DEFAULT_ANALYSIS_MODULE            "STD_ENKF"
#define DEFAULT_ANALYSIS_NUM_ITERATIONS    4
#define DEFAULT_ANALYSIS_ITER_CASE         "ITERATED_ENSEMBLE_SMOOTHER%d"
#define DEFAULT_ANALYSIS_ITER_RUNPATH      "Simulations/Real%d"
#define DEFAULT_ANALYSIS_MIN_REALISATIONS  0   // 0: No lower limit
#define DEFAULT_ANALYSIS_STOP_LONG_RUNNING false
#define DEFAULT_MAX_RUNTIME                0
#define DEFAULT_ITER_RETRY_COUNT           4


/* Default directories. */
#define DEFAULT_QC_PATH          "QC"
#define DEFAULT_REPORT_PATH      "reports"
#define DEFAULT_RUNPATH          "simulations/realization%d"
#define DEFAULT_ENSPATH          "storage"
#define DEFAULT_RFTPATH          "rft"
#define DEFAULT_REPORT_LARGE     false
#define DEFAULT_REPORT_TIMEOUT   120

#define DEFAULT_IMAGE_TYPE         "png"
#define DEFAULT_IMAGE_VIEWER       "/usr/bin/display"
#define DEFAULT_PLOT_LOGY          false

#define DEFAULT_STORE_PC           true
#define DEFAULT_PC_FILENAME        "PC_%04d-%04d-%s"
#define DEFAULT_PC_PATH            "PC"

#define SUMMARY_KEY_JOIN_STRING ":"
#define USER_KEY_JOIN_STRING    ":"

#define DEFAULT_WORKFLOW_VERBOSE false

/*
  Some #define symbols used when saving configuration files.
*/
#define CONFIG_OPTION_FORMAT        " %s:%s"
#define CONFIG_FLOAT_OPTION_FORMAT  " %s:%g"
#define CONFIG_KEY_FORMAT           "%-24s"
#define CONFIG_VALUE_FORMAT         " %-32s"
#define CONFIG_FLOAT_FORMAT         " %32.4f"  /* One size - fits all :-) */
#define CONFIG_INT_FORMAT           " %32d"    /* One size - fits all :-) */
#define CONFIG_SHORT_VALUE_FORMAT   " %-12s"
#define CONFIG_ENDVALUE_FORMAT      " %-32s\n"
#define CONFIG_COMMENT_FORMAT       "-- %s\n"
#define CONFIG_COMMENTLINE_FORMAT   "----------------------------------------------------------------------\n"

/*
   The string added at the beginning and end of string which should be
   replaced with the template parser.
*/

#define DEFAULT_START_TAG "<"
#define DEFAULT_END_TAG   ">"

#define DEFAULT_MANUAL_URL "http://ert.nr.no/ert/index.php/User_Manual"
#define DEFAULT_BROWSER    "firefox"

/*****************************************************************/

#define DEFAULT_VAR_DIR "/tmp/ert/var/run/ert"

/*****************************************************************/
/* file system spesific defaults. */

/**
  Name of the default case.
*/

#define CASE_LOG          "case-log"
#define CURRENT_CASE      "current"
#define DEFAULT_CASE      "default"
#define CURRENT_CASE_FILE "current_case"

#define DEFAULT_PLAIN_NODE_PARAMETER_PATH           "tstep/%04d/mem%03d/Parameter"
#define DEFAULT_PLAIN_NODE_STATIC_PATH              "tstep/%04d/mem%03d/Static"
#define DEFAULT_PLAIN_NODE_DYNAMIC_FORECAST_PATH    "tstep/%04d/mem%03d/Forecast"
#define DEFAULT_PLAIN_NODE_DYNAMIC_ANALYZED_PATH    "tstep/%04d/mem%03d/Analyzed"
#define DEFAULT_PLAIN_NODE_INDEX_PATH               "tstep/%04d/mem%03d/Index"

#define DEFAULT_PLAIN_VECTOR_PARAMETER_PATH           "vectors/mem%03d/Parameter"
#define DEFAULT_PLAIN_VECTOR_STATIC_PATH              "vectors/mem%03d/Static"
#define DEFAULT_PLAIN_VECTOR_DYNAMIC_FORECAST_PATH    "vectors/mem%03d/Forecast"
#define DEFAULT_PLAIN_VECTOR_DYNAMIC_ANALYZED_PATH    "vectors/mem%03d/Analyzed"
#define DEFAULT_PLAIN_VECTOR_INDEX_PATH               "vectors/mem%03d/Index"


#define DEFAULT_CASE_PATH                        "%s/files"              // mountpoint
#define DEFAULT_CASE_MEMBER_PATH                 "%s/mem%03d/files"      // mountpoint/member
#define DEFAULT_CASE_TSTEP_PATH                  "%s/%04d/files"         // mountpoint/tstep
#define DEFAULT_CASE_TSTEP_MEMBER_PATH           "%s/%04d/mem%03d/files" // mountpoint/tstep/member
// mountpoint = ENSPATH/case



#endif
