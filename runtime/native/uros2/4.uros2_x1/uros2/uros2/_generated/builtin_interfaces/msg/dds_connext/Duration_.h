

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Duration_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef Duration__937523578_h
#define Duration__937523578_h

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

            extern const char *Duration_TYPENAME;

            struct Duration_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class Duration_TypeSupport;
            class Duration_DataWriter;
            class Duration_DataReader;
            #endif

            class Duration_ 
            {
              public:
                typedef struct Duration_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef Duration_TypeSupport TypeSupport;
                typedef Duration_DataWriter DataWriter;
                typedef Duration_DataReader DataReader;
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

            NDDSUSERDllExport DDS_TypeCode* Duration__get_typecode(void); /* Type code */

            DDS_SEQUENCE(Duration_Seq, Duration_);

            NDDSUSERDllExport
            RTIBool Duration__initialize(
                Duration_* self);

            NDDSUSERDllExport
            RTIBool Duration__initialize_ex(
                Duration_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool Duration__initialize_w_params(
                Duration_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void Duration__finalize(
                Duration_* self);

            NDDSUSERDllExport
            void Duration__finalize_ex(
                Duration_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void Duration__finalize_w_params(
                Duration_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void Duration__finalize_optional_members(
                Duration_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool Duration__copy(
                Duration_* dst,
                const Duration_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace builtin_interfaces  */

#endif /* Duration_ */

