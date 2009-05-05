/***************************************************************************
 *   Copyright 2009 Last.fm Ltd.                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef TPLAYDAR_API_HPP
#define TPLAYDAR_API_HPP

// Policy needs to provide:
//
// void paramsAdd(ParamsT& p, StringT name, StringT value)
// UrlT createUrl(StringT base, StringT path, ParamsT p)

template <typename StringT, typename UrlT, typename ParamsT, typename Policy>
class TPlaydarApi : public Policy
{
public:
    TPlaydarApi(const StringT& baseUrl, const StringT& token)
        : m_baseUrl(baseUrl)
        , m_token(token)
    {
    }

    void setAuthToken(const StringT& token)
    {
        m_token = token;
    }

    UrlT auth1(const StringT& productName)
    {
        ParamsT params;
        paramsAdd( params, "website", productName);
        paramsAdd( params, "name", productName);
        return makeUrl("/auth/", params);
    }

    UrlT apiCall(const ParamsT& params)
    {
        return makeUrl("/api/", params);
    }

    UrlT stat()
    {
        ParamsT params;
        paramsAdd(params, "method", "stat");
        paramsAdd(params, "auth", m_token);
        return apiCall(params);
    }

    UrlT getResults(const StringT& qid)
    {
        ParamsT params;
        paramsAdd(params, "method", "get_results");
        paramsAdd(params, "qid", qid);
        paramsAdd(params, "auth", m_token);
        return apiCall(params);
    }

    // boffin does its own thing:
    UrlT boffinTagcloud()
    {
        ParamsT params;
        paramsAdd(params, "auth", m_token);
        return makeUrl("/boffin/tagcloud", params);
    }

    UrlT boffinRql(const StringT& rql)
    {
        ParamsT params;
        paramsAdd(params, "auth", m_token);
        return makeUrl("/boffin/rql/" + rql, params);
    }

private:
    UrlT makeUrl(const StringT& path, const ParamsT& params = ParamsT())
    {
        return createUrl(m_baseUrl, path, params);
    }

    StringT m_baseUrl;
    StringT m_token;
};

#endif