#include "triton/Dialect/Triton/IR/Dialect.h"
#include "triton/Dialect/TritonGPU/IR/Dialect.h"

#include "triton/Dialect/Triton/Transforms/Passes.h"
#include "triton/Dialect/TritonGPU/Transforms/Passes.h"

#include "triton/Conversion/Passes.h"

#include "mlir/IR/Dialect.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Support/MlirOptMain.h"

namespace mlir {
namespace test {
void registerTestAlignmentPass();
}
} // namespace mlir

int main(int argc, char **argv) {
  mlir::registerAllPasses();
  mlir::registerTritonPasses();
  mlir::registerTritonGPUPasses();
  mlir::test::registerTestAlignmentPass();
  mlir::triton::registerConvertTritonToTritonGPUPass();
  mlir::triton::registerConvertTritonGPUToLLVMPass();

  // TODO: register Triton & TritonGPU passes
  mlir::DialectRegistry registry;
  registry
      .insert<mlir::triton::TritonDialect, mlir::triton::gpu::TritonGPUDialect,
              mlir::arith::ArithmeticDialect, mlir::StandardOpsDialect,
              mlir::scf::SCFDialect>();

  return mlir::asMainReturnCode(mlir::MlirOptMain(
      argc, argv, "Triton (GPU) optimizer driver\n", registry));
}
