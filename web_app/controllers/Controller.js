const Api = require("../utils/Api");
const Utils = require("../utils/Utils");
const url = require("url");
const net = require("net");

exports.indexAction = async function(req, res) {
    res.render('index', {
        effects: Api.effets,
        palettes: Api.palettes,
        status: Api.status,
        apiIP: Api.address,
        primary: Utils.rgbToHex(Api.status.primary_color),
        secondary: Utils.rgbToHex(Api.status.secondary_color),
        tertiary: Utils.rgbToHex(Api.status.tertiary_color),
    });
}

exports.setAction = async function(req, res) {
    const params = url.parse(req.url, true).query;
    await Api.set(params);
    res.json(Api.status);
}

exports.pingAction = async function(req, res) {
    return res.json(await Api.ping());
}

exports.fetchAction = async function(req, res) {
    await Api.fetchStatus();
    return res.json(Api.status);
}

exports.refreshAction = async function(req, res) {
    await Api.fetchEffects();
    await Api.fetchPalettes();
    await Api.fetchStatus();
    res.redirect("/");
}

exports.netAction = async function(req, res) {
    let body = {};
    req.on('data', chunk => {
        let params = chunk.toString().split('&')
        for (let i in params) {
            let param = params[i].split('=');
            body[param[0]] = param[1];
        }
    });
    req.on('end', async () => {
        Api.setNetwork(body.net_ssid, body.net_pass, body.net_ip, body.net_gateway, body.net_mask)
        res.redirect("/");
    });
}

exports.configAction = async function(req, res) {
    let body = {};
    req.on('data', chunk => {
        let params = chunk.toString().split('&')
        for (let i in params) {
            let param = params[i].split('=');
            body[param[0]] = param[1];
        }
        if (net.isIPv4(body.ip))
            Api.address = body.ip;
    });
    req.on('end', async () => {
        res.redirect("/");
    });
}