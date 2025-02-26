//
// Created by Kenvi Zhu on 2022-01-10.
//

#include "../jni/org_wasmedge_ValidatorContext.h"
#include "AstModuleContext.h"
#include "ConfigureContext.h"
#include "common.h"
#include "jni.h"
#include "wasmedge/wasmedge.h"

WasmEdge_ValidatorContext *getValidatorContext(JNIEnv *env,
                                               jobject thisObject) {
  if (thisObject == NULL) {
    return NULL;
  }
  return (WasmEdge_ValidatorContext *)getPointer(env, thisObject);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ValidatorContext_validate(
    JNIEnv *env, jobject thisObject, jobject jAstModCxt) {
  WasmEdge_ValidatorContext *validatorContext =
      getValidatorContext(env, thisObject);
  WasmEdge_ASTModuleContext *astModCxt = getASTModuleContext(env, jAstModCxt);

  WasmEdge_Result result =
      WasmEdge_ValidatorValidate(validatorContext, astModCxt);
  handleWasmEdgeResult(env, &result);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ValidatorContext_nativeInit(
    JNIEnv *env, jobject thisObject, jobject jConfigCxt) {
  WasmEdge_ConfigureContext *configureContext =
      getConfigureContext(env, jConfigCxt);
  WasmEdge_ValidatorContext *validatorContext =
      WasmEdge_ValidatorCreate(configureContext);

  setPointer(env, thisObject, (long)validatorContext);
}

JNIEXPORT void JNICALL
Java_org_wasmedge_ValidatorContext_delete(JNIEnv *env, jobject thisObject) {
  WasmEdge_ValidatorContext *validatorContext =
      getValidatorContext(env, thisObject);
  WasmEdge_ValidatorDelete(validatorContext);
}