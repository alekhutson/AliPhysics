///
/// \file AddTaskFemtoSubtrains.C
///


#if !defined(__CINT__) && !defined(__CLING__)

#include "AliAnalysisTaskFemto.h"

#include <TString.h>
#include <TProofMgr.h>
#include <TProof.h>

#endif


/// Create Femtoscopy AliAnalysisTask
///
/*AliAnalysisTaskFemto *AddTaskFemto(

  TString configMacroName, 
TString containerName="femtolist", 
TString configMacroParameters="",  
Bool_t kGridConfig = kFALSE, 
TString userName = "", 
TString configFunName = "ConfigFemtoAnalysis")
*/
//configMacroName -> "alien:///alice/cern.ch/user/d/dowang/2021Pass2/UncerSys_testforpp.root",
//containerName->"dowang_0621_unsystest_18q_1",
//configMacroParameters->"1",
//kGridConfig-> kTRUE,
//userName->"alitrain"

//
AliAnalysisTaskFemto*
AddTaskFemtoSubtrainDowang(
                      TString rootName = "UncerSys_testforpp",
                      TString containerName="femtolist",
                      TString configMacroParameters="0",
                      TString userName = "alitrain",
                      TString subtrain="0"
                      )
{
  TString configMacroName = "alien:///alice/cern.ch/user/d/dowang/2021Pass2/"+rootName+".root";
  //TString configMacroName = "ConfigFemtoAnalysis.C";
  TString configFunName = "ConfigFemtoAnalysis";
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    ::Error("AddTaskFemto", "No analysis manager to connect to.");
    return NULL;
  }

  if (!mgr->GetInputEventHandler()) {
    ::Error("AddTaskFemto", "This task requires an input event handler");
    return NULL;
  }

  // Create the task, add it to manager.
  if (TProofMgr::GetListOfManagers()->GetEntries()) {
    gProof->Load(configMacroName);
  }

  // forward subtrain identifier to the macro
//   if (!subtrain.IsWhitespace()) {
//     configMacroParameters += ", \"" + subtrain + "\"";
//   }

 AliAnalysisTaskFemto *taskfemto;

  TString TaskFemtoStr = "TaskFemto";
  if (!subtrain.IsWhitespace()) {
    TaskFemtoStr += "_" + subtrain;
  }


  taskfemto = new AliAnalysisTaskFemto(TaskFemtoStr,configMacroName,configMacroParameters,kFALSE,kTRUE,userName, configFunName);
  //taskfemto = new AliAnalysisTaskFemto("TaskFemto",configMacroName,configMacroParameters,kFALSE);



  mgr->AddTask(taskfemto);

  // Get and connect other common input/output containers via the manager
  if (!subtrain.IsWhitespace()) {
    containerName += "_" + subtrain;
  }

  TString outputfile = AliAnalysisManager::GetCommonFileName();
  outputfile += ":PWG2FEMTO";

  AliAnalysisDataContainer *cout_femto
    = mgr->CreateContainer(containerName,
                           TList::Class(),
                           AliAnalysisManager::kOutputContainer,
                           outputfile);

   mgr->ConnectInput(taskfemto, 0, mgr->GetCommonInputContainer());
   mgr->ConnectOutput(taskfemto, 0, cout_femto);

   return taskfemto;
}
