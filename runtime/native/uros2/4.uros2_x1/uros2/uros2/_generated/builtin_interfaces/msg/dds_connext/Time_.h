

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Time_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef Time__2038546381_h
#define Time__2038546381_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

namespace builtin_interfaces {
    namespace msg {
        namespace dds_ {

            extern const char *Time_TYPENAME;

            struct Time_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class Time_TypeSupport;
            class Time_DataWriter;
            class Time_DataReader;
            #endif

            class Time_ 
            {
              public:
                typedef struct Time_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef Time_TypeSupport TypeSupport;
                typedef Time_DataWriter DataWriter;
                typedef Time_DataReader DataReader;
                #endif

                DDS_Long   sec_ ;
                DDS_UnsignedLong   nanosec_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* Time__get_typecode(void); /* Type code */

            DDS_SEQUENCE(Time_Seq, Time_);

            NDDSUSERDllExport
            RTIBool Time__initialize(
                Time_* self);

            NDDSUSERDllExport
            RTIBool Time__initialize_ex(
                Time_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool Time__initialize_w_params(
                Time_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void Time__finalize(
                Time_* self);

            NDDSUSERDllExport
            void Time__finalize_ex(
                Time_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void Time__finalize_w_params(
                Time_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void Time__finalize_optional_members(
                Time_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool Time__copy(
                Time_* dst,
                const Time_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace builtin_interfaces  */

#endif /* Time_ */

