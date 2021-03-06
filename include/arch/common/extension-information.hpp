/*
* C++ Assembler Interpreter
* Copyright (C) 2016 Chair of Computer Architecture
* at Technical University of Munich
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ERAGPSIM_ARCH_EXTENSION_INFORMATION_HPP
#define ERAGPSIM_ARCH_EXTENSION_INFORMATION_HPP

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "arch/common/information.hpp"
#include "arch/common/unit-information.hpp"
#include "common/builder.hpp"
#include "common/optional.hpp"
#include "common/utility.hpp"

class InstructionSet;

/**
 * Holds information about an extension.
 *
 * In our model, an architecture is split into one or many extensions. An
 * extension is then further composed mainly of three things:
 * 1. One or more units, such as a CPU.
 * 2. An instruction set.
 * 3. Auxiliary information, such as word size or endiannss.
 * An architecture can then be built by specifying a base-extension and
 * optionally stacking any further extension on top of that base. This allows
 * for a highly modular design, as envisioned by the creators of RISC-V. Note
 * that this also means that an extension may be a complete architecture in
 * itself, if it defines at least one unit and one instruction, but must not
 * necessarily be. For example, RVA32/64 extensions define only additional
 * instructions (for atomic operations), but no additional unit (hardware
 * registers).
 *
 * An `ExtensionInformation` can be built easily on-top of anther via the
 * supported interface. In general, the API follows the Builder pattern.
 */
class ExtensionInformation : public Builder {
 public:
  using size_t            = unsigned short;
  using UnitContainer     = std::vector<UnitInformation>;
  using UnitList          = std::initializer_list<UnitInformation>;
  using ExtensionList     = std::initializer_list<ExtensionInformation>;
  using Endianness        = Information::Endianness;
  using AlignmentBehavior = Information::AlignmentBehavior;

  /**
   * Constructs a new `ExtensionInformation` object.
   *
   * @param name The name of the extension.
   */
  explicit ExtensionInformation(const std::string& name);

  /**
   * Copies the extension information from another instance.
   *
   * @param other Another `ExtensionInformation` object.
   */
  ExtensionInformation(const ExtensionInformation& other);

  /**
   * Move-copies the extension information from another instance.
   *
   * @param other Another `ExtensionInformation` object.
   */
  ExtensionInformation(ExtensionInformation&& other) noexcept;

  /**
   * Assigns the extension information to another instance.
   *
   * @param other Another `ExtensionInformation` object.
   */
  ExtensionInformation& operator=(ExtensionInformation other);

  /**
   * Destructs the extension information.
   */
  ~ExtensionInformation();

  /**
   * Swaps the contents of this object with another `ExtensionInformation`
   * instance.
   *
   * @param other Another `ExtensionInformation` object.
   */
  void swap(ExtensionInformation& other) noexcept;

  /**
   * Swaps the contents of one `ExtensionInformation` instance with another
   * instance.
   *
   * @param first The one `ExtensionInformation` instance.
   * @param second The other `ExtensionInformation` instance.
   */
  friend void
  swap(ExtensionInformation& first, ExtensionInformation& second) noexcept;

  /**
   * Merges the information in this instance with those of another
   * `ExtensionInformation` object.
   *
   * @param other Another `ExtensionInformation` object.
   *
   * @return The current
   *
   * @see getMerge()
   */
  ExtensionInformation& operator+=(const ExtensionInformation& other);

  /**
   * Merges the extension with a range of other extensions.
   *
   * See getMerge() for exact information on how an extension is merged.
   *
   * @tparam A range-like sequence type.
   *
   * @param range The range of extensions to merge to merge.
   *
   * @return The current `ExtensionInformation` object.
   *
   * @see getMerge()
   */
  template <typename Range>
  ExtensionInformation& operator+=(const Range& range) {
    return merge(range);
  }

  /**
   * Returns a copy of the object resulting from merging this one with another
   * `ExtensionInformation` instance, without modifying this instance.
   *
   * @param other Another ExtensionInformation object.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation operator+(const ExtensionInformation& other) const;

  /**
   * Sets the name of the extension.
   *
   * @param name The new name for the extension.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& name(const std::string& name);

  /**
   * Returns the name of the extension.
   */
  const std::string& getName() const noexcept;

  /**
   * Sets the endianness for the extension.
   *
   * @param endianness The `Endianness` member to assign to the extension.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& endianness(Endianness endianness);

  /**
   * Returns the endianness of the extension.
   */
  Endianness getEndianness() const noexcept;

  /**
   * Returns whether any endianness is set.
   */
  bool hasEndianness() const noexcept;

  /**
   * Sets the alignment behavior for the extension.
   *
   * @param alignment behavior The `AlignmentBehavior` member to assign to the
   * extension.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& alignmentBehavior(AlignmentBehavior alignmentBehavior);

  /**
   * Returns the alignment behavior of the extension, if any.
   */
  AlignmentBehavior getAlignmentBehavior() const noexcept;

  /**
   * Returns whether any alignment behavior of the extension is set.
   */
  bool hasAlignmentBehavior() const noexcept;

  /**
   * Sets the word size for the extension, in bits.
   *
   * @param wordSize The word size for the extension, in bits.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& wordSize(size_t wordSize);

  /**
   * Returns the word size of the extension (in bits), if any.
   */
  size_t getWordSize() const noexcept;

  /**
   * Returns whether any word size is set.
   */
  bool hasWordSize() const noexcept;

  /**
   * Adds the instructions of the instruction set to the extension.
   *
   * @param instructions The instructions to add to the extension.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& addInstructions(const InstructionSet& instructions);

  /**
   * Sets the instructions of the extension to those given.
   *
   * @param instructions The instructions to assign for the extension.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& setInstructions(const InstructionSet& instructions);

  /**
   * Returns the instructions of the extension.
   */
  const InstructionSet& getInstructions() const noexcept;

  /**
   * Adds the units in the range to those of the extension.
   *
   * @tparam Range A range-like sequence.
   *
   * @param range The range of units to add.
   *
   * @return The current `ExtensionInformation` object.
   */
  template <typename Range>
  ExtensionInformation& addUnits(const Range& range) {
    Utility::concatenate(_units, range);

    return *this;
  }

  /**
   * Adds the units in the list to those of the extension.
   *
   * @param list The list of units to add.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& addUnits(UnitList units);

  /**
   * Adds the unit in the list to those of the extension.
   *
   * @param unit The unit to add.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& addUnit(const UnitInformation& unit);

  /**
   * Returns the units of the extension.
   */
  const UnitContainer& getUnits() const noexcept;

  /**
   * Merges the extension with a range of other extensions.
   *
   * See getMerge() for exact information on how an extension is merged.
   *
   * @tparam A range-like sequence type.
   *
   * @param range The range of extensions to merge to merge.
   *
   * @return The current `ExtensionInformation` object.
   *
   * @see getMerge()
   */
  template <typename Range>
  ExtensionInformation& merge(const Range& range) {
    for (auto& extension : range) merge(extension);

    return *this;
  }

  /**
   * Merges the extension with a list of other extensions.
   *
   * See getMerge() for exact information on how an extension is merged.
   *
   * @param list The list of extensions to merge.
   *
   * @return The current `ExtensionInformation` object.
   *
   * @see getMerge()
   */
  ExtensionInformation& merge(ExtensionList list);

  /**
   * Merges the extension with another extension.
   *
   * Merging means that the instructions and units of the other extension are
   * added to this one. Also, any member that is present in the other extension,
   * meaning that it was assigned at one point (the optional is not empty), are
   * set to override the values stored in this extension. The only exception to
   * this rule is the name member of this extension, which is never overriden.
   *
   * @param otherExtension The other extension to merge with.
   *
   * @return The current `ExtensionInformation` object.
   */
  ExtensionInformation& merge(const ExtensionInformation& otherExtension);

  /** @copydoc builder::isValid() */
  bool isValid() const noexcept override;

  /**
  * Checks if the extension is a valid base extension.
  *
  * If true, this extension can be used as a base extension. This means that it
  * defines all necessary attributes for a basic ISA, including the endianness,
  * alignment behavior and word size, at least one unit and at least one
  * instruction.
  */
  bool isValidBase() const noexcept;

 private:
  ExtensionInformation() noexcept;

  /** The name of the extension. */
  std::string _name;

  /** The endianness of the extension, if any. */
  Optional<Endianness> _endianness;

  /** The alignment behavior of the extension, if any. */
  Optional<AlignmentBehavior> _alignmentBehavior;

  /** The word size of the extension, if any. */
  Optional<size_t> _wordSize;

  /** The instruction set for the extension, if any. */
  std::unique_ptr<InstructionSet> _instructions;

  /** The units supplied by the extension, if any. */
  UnitContainer _units;
};

#endif /* ERAGPSIM_ARCH_EXTENSION_INFORMATION_HPP */
