/* Copyright 2018 by Multy.io
 * Licensed under Multy.io license
 *
 * See LICENSE for details
 */

#include "value_printers.h"

#include "multy_test/bip39_test_cases.h"
#include "multy_test/utility.h"

#include "multy_core/common.h"
#include "multy_core/error.h"

#include "multy_core/src/account_base.h"
#include "multy_core/src/api/big_int_impl.h"
#include "multy_core/src/api/key_impl.h"
#include "multy_core/src/api/transaction_impl.h"
#include "multy_core/src/utility.h"

#include "wally_elements.h"

namespace
{
using namespace test_utility;
using namespace multy_core::internal;

std::ostream& operator<<(std::ostream& ostr, HDPath const& path)
{
    ostr << "m";
    for (const auto i : path)
    {
        ostr << "/" << i;
    }
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, BinaryData const& data)
{
    return ostr << (data.data ? to_hex(data) : std::string("<null>")) << ", "
                << data.len;
}

std::ostream& operator<<(std::ostream& ostr, Currency currency)
{
    switch (currency)
    {
        case CURRENCY_BITCOIN:
            ostr << "CURRENCY_BITCOIN";
            break;
        case CURRENCY_ETHEREUM:
            ostr << "CURRENCY_ETHEREUM";
            break;
        default:
            ostr << "unknown currency " << static_cast<uint32_t>(currency);
            break;
    }
    return ostr;
}

} // namespace

namespace std
{

void PrintTo(const std::nullptr_t&, std::ostream* out)
{
    *out << "<nullptr>";
}

} // namespace std

void PrintTo(const Error& e, std::ostream* out)
{
    *out << "Error{ " << e.code << ", \"" << e.message << "\" }";
    if (e.location.file)
    {
        *out << " @ " << e.location.file << " : " << e.location.line;
    }
}

void PrintTo(const BinaryData& data, std::ostream* out)
{
    *out << "BinaryData{ " << data << " }";
}

void PrintTo(const Key& key, std::ostream* out)
{
    *out << "Key{ " << key.to_string() << " }";
}

void PrintTo(const ExtendedKey& key, std::ostream* out)
{
    *out << "ExtendedKey{" << key.to_string() << " }";
}

void PrintTo(const BIP39TestCase& e, std::ostream* out)
{
    *out << "BIP39TestCase{\n"
         << "\tenropy: " << e.entropy << ",\n"
         << "\tmnemonic: \"" << e.mnemonic << "\",\n"
         << "\tseed: " << e.seed << ",\n"
         << "\troot key: " << e.root_key << "\n"
         << "}";
}

void PrintTo(const Account& a, std::ostream* out)
{
    *out << "Account{\n"
         << "\tcurrency: " << a.get_currency() << ",\n"
         << "\tpath: " << a.get_path() << "\n"
         << "}";
}

void PrintTo(const HDAccount& a, std::ostream* out)
{
    *out << "HDAccount{\n"
         << "\tcurrency: " << a.get_currency() << ",\n"
         << "\tpath: " << a.get_path() << "\n"
         << "}";
}

void PrintTo(const Currency& c, std::ostream* out)
{
    *out << c;
}

void PrintTo(const AddressType& a, std::ostream* out)
{
    switch (a)
    {
        case ADDRESS_EXTERNAL:
            *out << "ADDRESS_EXTERNAL";
            break;
        case ADDRESS_INTERNAL:
            *out << "ADDRESS_INTERNAL";
            break;
        default:
            *out << "unknown address " << a;
            break;
    }
}

void PrintTo(const Transaction& t, std::ostream* out)
{
    *out << "Transaction {" << t.get_currency() << "}";
}

void PrintTo(const BigInt& a, std::ostream* out)
{
    *out << "BigInt {" << a.get_value() << "}";
}
