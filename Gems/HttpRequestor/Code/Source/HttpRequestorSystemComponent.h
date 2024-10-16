/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include "HttpRequestManager.h"
#include <AzCore/Component/Component.h>
#include <HttpRequestor/HttpRequestorBus.h>
#include <aws/core/client/ClientConfiguration.h>

namespace HttpRequestor
{
    class HttpRequestorSystemComponent
        : public AZ::Component
        , protected HttpRequestorRequestBus::Handler
    {
    public:
        AZ_COMPONENT(HttpRequestorSystemComponent, "{CF29468F-1F67-497F-B4FF-C0F123584864}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);
        
    protected:
        ////////////////////////////////////////////////////////////////////////
        // HttpRequestorRequestBus interface implementation
        ////////////////////////////////////////////////////////////////////////
        void AddRequest(const AZStd::string& URI, Aws::Http::HttpMethod method, const Callback& callback) override;

        void AddRequestWithClientConfiguration(
            const AZStd::string& URI,
            Aws::Http::HttpMethod method,
            const Callback& callback,
            const Aws::Client::ClientConfiguration clientConfiguration) override;

        void AddRequestWithHeaders(
            const AZStd::string& URI, Aws::Http::HttpMethod method, const Headers& headers, const Callback& callback) override;

        void AddRequestWithHeadersAndClientConfiguration(
            const AZStd::string& URI,
            Aws::Http::HttpMethod method,
            const Headers& headers,
            const Callback& callback,
            const Aws::Client::ClientConfiguration clientConfiguration) override;

        void AddRequestWithHeadersAndBody(
            const AZStd::string& URI,
            Aws::Http::HttpMethod method,
            const Headers& headers,
            const AZStd::string& body,
            const Callback& callback) override;

        void AddRequestWithHeadersBodyAndClientConfiguration(
            const AZStd::string& URI,
            Aws::Http::HttpMethod method,
            const Headers& headers,
            const AZStd::string& body,
            const Callback& callback,
            const Aws::Client::ClientConfiguration clientConfiguration) override;

        void AddTextRequest(const AZStd::string& URI, Aws::Http::HttpMethod method, const TextCallback& callback) override;

        void AddTextRequestWithClientConfiguration(
            const AZStd::string& URI,
            Aws::Http::HttpMethod method,
            const TextCallback& callback,
            const Aws::Client::ClientConfiguration clientConfiguration) override;

        void AddTextRequestWithHeaders(
            const AZStd::string& URI, Aws::Http::HttpMethod method, const Headers& headers, const TextCallback& callback) override;

        void AddTextRequestWithHeadersAndClientConfiguration(
            const AZStd::string& URI,
            Aws::Http::HttpMethod method,
            const Headers& headers,
            const TextCallback& callback,
            const Aws::Client::ClientConfiguration clientConfiguration = Aws::Client::ClientConfiguration()) override;

        void AddTextRequestWithHeadersAndBody(
            const AZStd::string& URI,
            Aws::Http::HttpMethod method,
            const Headers& headers,
            const AZStd::string& body,
            const TextCallback& callback) override;

        void AddTextRequestWithHeadersBodyAndClientConfiguration(
            const AZStd::string& URI,
            Aws::Http::HttpMethod method,
            const Headers& headers,
            const AZStd::string& body,
            const TextCallback& callback,
            const Aws::Client::ClientConfiguration clientConfiguration = Aws::Client::ClientConfiguration()) override;

        AZStd::chrono::milliseconds GetLastRoundTripTime() const override;

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////

    private:
        ManagerPtr              m_httpManager;
    };
}

