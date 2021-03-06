#pragma once

#include <torch/data/samplers/base.h>
#include <torch/types.h>
#include <torch/csrc/WindowsTorchApiMacro.h>

#include <cstddef>
#include <vector>

namespace torch {
namespace serialize {
class OutputArchive;
class InputArchive;
} // namespace serialize
} // namespace torch

namespace torch {
namespace data {
namespace samplers {

/// A `Sampler` that returns random indices.
class RandomSampler : public Sampler<> {
 public:
  /// Constructs a `RandomSampler` with a size and dtype for the stored indices.
  ///
  /// The constructor will eagerly allocate all required indices, which is the
  /// sequence `0 ... size - 1`. `index_dtype` is the data type of the stored
  /// indices. You can change it to influence memory usage.
  TORCH_API explicit RandomSampler(int64_t size, Dtype index_dtype = torch::kInt64);

  /// Resets the `RandomSampler` to a new set of indices.
  TORCH_API void reset() override;

  /// Returns the next batch of indices.
  TORCH_API optional<std::vector<size_t>> next(size_t batch_size) override;

  /// Serializes the `RandomSampler` to the `archive`.
  TORCH_API void save(serialize::OutputArchive& archive) const override;

  /// Deserializes the `RandomSampler` from the `archive`.
  TORCH_API void load(serialize::InputArchive& archive) override;

  /// Returns the current index of the `RandomSampler`.
  TORCH_API size_t index() const noexcept;

 private:
  Tensor indices_;
  int64_t index_ = 0;
};
} // namespace samplers
} // namespace data
} // namespace torch
