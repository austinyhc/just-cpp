local M = require "moses"
local https = require("ssl.https")
local ltn12 = require('ltn12')
local cjson = require("cjson")

local URL = "https://leetcode.com/api/problems/algorithms"
local body = {}

local res, code, headers, status = http.request{
    url = URL,
    method = "GET",
    sink = ltn12.sink.table(body),
    protocol = "tlsv1"

}
print(res, code, headers, status)
print(ltn12.sink.table(body))

-- local response = table.concat(body)
-- print(response)

local function fetch_problems()
end

local function ()
end
