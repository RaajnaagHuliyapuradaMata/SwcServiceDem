#pragma once
/******************************************************************************/
/* File   : ServiceDem.hpp                                                    */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "infServiceDem_ServiceNvM_Types.hpp"
#include "CfgServiceDem.hpp"
#include "ServiceDem_core.hpp"
#include "infServiceDem_Exp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_ServiceDem:
      INTERFACES_EXPORTED_SERVICEDEM
   ,  public abstract_module
   ,  public class_ServiceDem_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstModule_TypeAbstract* lptrNvMBlocksRom = (ConstModule_TypeAbstract*)NULL_PTR;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, SERVICEDEM_CODE) InitFunction(
            CONSTP2CONST(ConstModule_TypeAbstract, SERVICEDEM_CONST,       SERVICEDEM_APPL_CONST) lptrNvMBlocksRomModule
         ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICEDEM_CONFIG_DATA, SERVICEDEM_APPL_CONST) lptrCfgModule
      );
      FUNC(void, SERVICEDEM_CODE) DeInitFunction (void);
      FUNC(void, SERVICEDEM_CODE) MainFunction   (void);
      SERVICEDEM_CORE_FUNCTIONALITIES

      FUNC(void, SERVICEDEM_CODE) PreInit        (void);
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern VAR(module_ServiceDem, SERVICEDEM_VAR) ServiceDem;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
