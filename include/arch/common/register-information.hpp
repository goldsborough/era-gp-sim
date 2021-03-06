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

#ifndef ERAGPSIM_ARCH_REGISTER_INFORMATION_HPP
#define ERAGPSIM_ARCH_REGISTER_INFORMATION_HPP

#include <cassert>
#include <cstddef>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

#include "common/builder.hpp"
#include "common/optional.hpp"

/**
 * Holds information about a register.
 *
 * This class contains all the necessary information about a register, as may be
 * required by other modules. For example, it provides configuration of the
 * name, size, numeric ID or aliases. Every register is always associated with a
 * certain *type*, describing the characteristics of the register. Most often
 * the register will be a processor-register and thus of integral type. However,
 * the register could also be an FPU register or hold vector data. As an ISA may
 * require that certain registers are hardwired to some constant, like 0 (the x0
 * register in RISC-V) or Pi, this class can also store information about any
 * hardwired constant. To keep the class template-less, the constant is stored
 * as a floating-point value. This is most certainly a hack and quite ugly, but
 * prevents the need to propagate template parameters into enclosing classes
 * (e.g. `Unit` or `Architecture`).
 *
 * The class' interface is intended to support the Builder pattern. As such, it
 * defaults certain values internally:
 *
 * - The type defauls to `Type::INTEGER`.
 * - The ID defaults to an instance-unique (static), incrementing ID.
 */
class RegisterInformation : public Builder {
 public:
  using id_t   = std::size_t;
  using size_t = unsigned short;

  /** The type of data stored in this register. */
  enum class Type { INTEGER, FLOAT, VECTOR, FLAG, INSTRUCTION };

  /**
   * Constructs the RegisterInformation with the register's name.
   *
   * @param name The name of the register.
   */
  explicit RegisterInformation(const std::string& name);

  /**
   * Constructs the RegisterInformation with the register's name and size.
   *
   * @param name The name of the register.
   * @param size The size of the register.
   */
  RegisterInformation(const std::string& name, size_t size);

  /**
   * Sets the name of the register.
   *
   * @param name The new name for the register.
   *
   * @return The current register object.
   */
  RegisterInformation& name(const std::string& name);

  /**
   * Returns the name of the register.
   *
   * @return The name of the register.
   */
  const std::string& getName() const noexcept;

  /**
   * Sets the size (width) of the register, in bits.
   *
   * @param bit_size The new width for the register, in bits.
   *
   * @return The current register object.
   */
  RegisterInformation& size(size_t bit_size);

  /**
   * Returns the size of the register, if any.
   *
   * @return The size of the register.
   */
  size_t getSize() const noexcept;

  /**
   * Returns whether the register has a size set.
   */
  bool hasSize() const noexcept;

  /**
   * Sets the numeric identifier for the register.
   *
   * @param id The new numeric ID for the register.
   *
   * @return The current register object.
   */
  RegisterInformation& id(id_t id);

  /**
   * Returns the ID of the register.
   */
  id_t getID() const noexcept;

  /**
   * Sets the type of the register.
   *
   * Must be a member of the `Type` enum and therefore
   * one of {INTEGER, FLOAT, VECTOR, FLAG}.
   *
   * @param type The new type for the register.
   *
   * @return The current register object.
   */
  RegisterInformation& type(Type type);

  /**
   * Returns the type of the register.
   *
   * @return The type of the register.
   */
  Type getType() const noexcept;

  /**
   * Sets the register to be hardwired to the given constant.
   *
   * The constant value must be convertible to `double` (that is the internal
   * storage type, also for integral types).
   *
   * @param constant The new hardwired constant.
   *
   * @return The current register object.
   */
  template <typename ConstantType,
            typename = std::enable_if_t<
                std::is_convertible<ConstantType, double>::value>>
  RegisterInformation& constant(const ConstantType& constant) {
    _constant = constant;
    return *this;
  }

  /**
   * Returns the constant the register is hardwired to, if any, and converts it
   *  to the given type.
   *
   * @tparam ConstantType The output type for the constant.
   *
   * @return If a conversion is possible, the current hardwired constant
   *         cast to the given type.
   */
  template <typename ConstantType,
            typename = std::enable_if_t<
                std::is_convertible<ConstantType, double>::value>>
  ConstantType getConstant() const noexcept {
    assert(isConstant());
    return static_cast<ConstantType>(*_constant);
  }

  /**
   * Returns whether or not the register is currently hardwired to any constant.
   *
   * @return True if the register is hardwired to a constant, else false.
   */
  bool isConstant() const noexcept;

  /**
   * Adds a range of addAliases to the known aliases for the register.
   *
   * @tparam Range A range-like type.
   *
   * @param range A range of new aliases.
   *
   * @return The current register object.
   */
  template <typename Range>
  RegisterInformation& addAliases(const Range& range) {
    using std::begin;
    using std::end;
    _aliases.insert(_aliases.end(), begin(range), end(range));

    return *this;
  }

  /**
   * Adds the list of aliases to the known aliases for the register.
   *
   * @param aliases A list of aliases.
   *
   * @return The current register object.
   */
  RegisterInformation& addAliases(std::initializer_list<std::string> aliases);

  /**
   * Adds the given alias to the known aliases for the register.
   *
   * @param alias The alias to assign to the register.
   *
   * @return The current register object.
   */
  RegisterInformation& addAlias(const std::string& alias);

  /**
   * Returns the known aliases for the register.
   *
   * @return The currently known aliases for the register.
   */
  const std::vector<std::string>& getAliases() const noexcept;

  /**
   * Returns whether or not the register has aliases at all.
   *
   * @return True if the register has at least one alias, else false.
   */
  bool hasAliases() const noexcept;

  /**
   * Sets the ID of the enclosing register.
   *
   * This is the numeric identifier of the register that contains this
   * register. For example, it would be EAX if this register was AX.
   *
   * @return The current register object.
   */
  RegisterInformation& enclosing(id_t id);

  /**
   * Returns the enclosing register ID, if any.
   *
   * If this register is a part of another, enclosing register, then this
   * method returns that enclosing register's ID. For example, AX will have
   * the ID for EAX in this variable. Note that not all registers have an
   * enclosing register ID (e.g. EAX on 32-bit systems).
   *
   * @return An Optional object, possibly containing an ID for the enclosing
   *         register (if this register has an enclosing register).
   */
  id_t getEnclosing() const noexcept;


  /**
   * Returns whether or not the register has an enclosing ID set.
   */
  bool hasEnclosing() const noexcept;

  /**
   * Adds a range of constituent register IDs for the register.
   *
   * See getConstituents() for a description of a register's consituents.
   *
   * @tparam A range-like type.
   *
   * @param range A range of new constituents.
   *
   * @return The current register object.
   */
  template <typename Range>
  RegisterInformation& addConstituents(const Range& range) {
    using std::begin;
    using std::end;
    _constituents.insert(_constituents.end(), begin(range), end(range));

    return *this;
  }

  /**
   * Adds a list of constituent register IDs for the register.
   *
   * See getConstituents() for a description of a register's consituents.
   *
   * @param constituents The list of constituents to be added for the register.
   *
   * @return The current register object.
   */
  RegisterInformation&
  addConstituents(std::initializer_list<id_t> constituents);

  /**
   * Adds a single consituent ID for the register.
   *
   * See getConstituents() for a description of a register's consituents.
   *
   * @param id The ID of the constituent register to add.
   *
   * @return The current register object.
   */
  RegisterInformation& addConstituent(id_t id);

  /**
   * Returns the constituent IDs of the register.
   *
   * The constituent IDs are the IDs of the registers that this register
   * contains *directly*. *Directly* means that if the register is viewed
   * as a node in a tree, only its direct neighbors (distance 1) are contained.
   * For example, if this register represents EAX, it would contain only AX and
   * not AH or AL, because those are then contained by AX.
   *
   * @return The constituent IDs of the register.
   */
  const std::vector<id_t>& getConstituents() const noexcept;

  /**
   * Returns whether or not the register has constituents at all.
   *
   * @return True if the register has at least one constituent, else false.
   */
  bool hasConstituents() const noexcept;

  /** @copydoc Builder::isValid() */
  bool isValid() const noexcept override;

 private:
  /** An ID that increments for each new created instance (for default IDs). */
  static id_t _rollingID;

  /*
  static constexpr Type _typeDefault = std::conditional<
      std::is_floating_point<HardwiredType>::value,
      std::integral_constant<Type, Type::FLOAT>,
      std::integral_constant<Type, Type::INTEGER>>::type::value;
  */

  /** The numeric ID of the register. */
  id_t _id;

  /** The type of the register. */
  Type _type;

  /** The name of the register, e.g. "EAX". */
  std::string _name;

  /** The size of the register, in bits. */
  Optional<size_t> _size;

  /** The constant the register is hardwired to, if any. */
  Optional<double> _constant;

  /** The ID of the register's enclosing register, if one exists. */
  Optional<id_t> _enclosing;

  /** The IDs of the register's directly constituent registers, if any exist. */
  std::vector<id_t> _constituents;

  /** The aliases of the register, if any. */
  std::vector<std::string> _aliases;
};

#endif /* ERAGPSIM_ARCH_REGISTER_INFORMATION_HPP */
