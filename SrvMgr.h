//
// Fulcrum - A fast & nimble SPV Server for Bitcoin Cash
// Copyright (C) 2019-2020  Calin A. Culianu <calin.culianu@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program (see LICENSE.txt).  If not, see
// <https://www.gnu.org/licenses/>.
//
#pragma once

#include "Mgr.h"
#include "Options.h"

#include <list>
#include <memory>

class BitcoinDMgr;
class Server;
class Storage;

class SrvMgr : public Mgr
{
    Q_OBJECT
public:
    explicit SrvMgr(const std::shared_ptr<Options> & options,
                    const std::shared_ptr<Storage> & storage,
                    const std::shared_ptr<BitcoinDMgr> & bitcoindmgr,
                    QObject *parent = nullptr);
    ~SrvMgr() override;
    void startup() override; // may throw on error
    void cleanup() override;

    int nServers() const { return int(servers.size()); }

signals:
    /// Notifies all blockchain.headers.subscribe'd clients for the entire server about a new header.
    /// (normally connected to the Controller::newHeader signal).
    void newHeader(unsigned height, const QByteArray &header);

protected:
    Stats stats() const override;

private:
    void startServers();
    const std::shared_ptr<Options> options;
    std::shared_ptr<Storage> storage;
    std::shared_ptr<BitcoinDMgr> bitcoindmgr;
    std::list<std::unique_ptr<Server>> servers;
};
