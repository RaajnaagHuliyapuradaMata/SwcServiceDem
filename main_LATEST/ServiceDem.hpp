#pragma once
/******************************************************************************/
/* File   : ServiceDem.hpp                                                           */
/*                                                                            */
/* Author : Nagaraja HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Nagaraja HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/NagarajaHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "ConstServiceDem.hpp"
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
      const ConstServiceDem_Type* lptrConst = (ConstServiceDem_Type*)NULL_PTR;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, SERVICEDEM_CODE) InitFunction(
            CONSTP2CONST(ConstModule_TypeAbstract, SERVICEDEM_CONST,       SERVICEDEM_APPL_CONST) lptrConstModule
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

