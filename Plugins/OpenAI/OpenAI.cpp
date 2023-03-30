#include "API/CNWSModule.hpp"
#include "nwnx.hpp"

#include "External/json/json.hpp"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "External/httplib.h"

#include <future>

using namespace NWNXLib;

// from webhook
static std::string escape_json(const std::string& s) {
    std::ostringstream o;
    for (auto c = s.cbegin(); c != s.cend(); c++) {
        if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f')) {
            o << "\\u"
                << std::hex << std::setw(4) << std::setfill('0') << (int)*c;
        }
        else {
            o << *c;
        }
    }
    return o.str();
}

void DoRequest(const json& messages, const std::string& id, const std::string& model, const float randomness, const int maxTokens)
{
    httplib::Client client("https://api.openai.com");
    client.enable_server_certificate_verification(false);
    client.set_read_timeout(std::chrono::seconds(60));
    client.set_write_timeout(std::chrono::seconds(60));

    // See https://platform.openai.com/docs/api-reference/completions/create
    httplib::Headers header = {
        { "Authorization", "Bearer " + Config::Get<std::string>("TOKEN", "SET_ENV_CONFIG") }
    };

    std::string params = R"(
    {
        "model": "$1",
        "messages": $2,
        "temperature": $3,
        "max_tokens": $4
    })";

    params.replace(params.find("$1"), 2, escape_json(String::ToUTF8(model)));
    params.replace(params.find("$2"), 2, messages.dump());
    params.replace(params.find("$3"), 2, std::to_string(randomness));
    params.replace(params.find("$4"), 2, std::to_string(maxTokens));

    LOG_INFO("Making request %s", params.c_str());
    httplib::Result result = client.Post("/v1/chat/completions", header, params, "application/json");

    if (result)
    {
        LOG_INFO("Got result %s", result->body.c_str());

        json bodyAsJson = json::parse(result->body);
        const std::string text = bodyAsJson["choices"][0]["message"]["content"];

        Tasks::QueueOnMainThread([=]()
            {
                auto moduleOid = NWNXLib::Utils::ObjectIDToString(Utils::GetModule()->m_idSelf);
                MessageBus::Broadcast("NWNX_EVENT_PUSH_EVENT_DATA", { "RESPONSE", text });
                MessageBus::Broadcast("NWNX_EVENT_PUSH_EVENT_DATA", { "REQUEST_ID", id });
                MessageBus::Broadcast("NWNX_EVENT_SIGNAL_EVENT", { "NWNX_ON_OPENAI_RESPONSE", moduleOid });
            });
    }
    else
    {
        LOG_ERROR("Failed to make request due to: '%s'", httplib::to_string(result.error()).c_str());
    }
}

NWNX_EXPORT ArgumentStack ChatAsync(ArgumentStack&& args)
{
    const json messages = args.extract<JsonEngineStructure>().m_shared->m_json;
    const std::string id = args.extract<std::string>();
    const std::string model = args.extract<std::string>();
    const float randomness = args.extract<float>();
    const int maxTokens = args.extract<int>();
    std::async(std::launch::async, &DoRequest, messages, id, model, randomness, maxTokens);
    return {};
}
