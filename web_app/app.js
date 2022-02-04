#!/usr/bin/env node

'use strict';

const express    = require('express');
const { Liquid } = require('liquidjs');
const path       = require("path");
const Api        = require("./utils/Api");
const app        = express();
const router 	 = express.Router();
const port 	     = process.env.PORT || 8888;

const engine = new Liquid({
    root: path.resolve(__dirname, 'templates/'),
    extname: '.liquid',
    cache: process.env.NODE_ENV === 'production'
});

app.engine('liquid', engine.express());
app.set('views', './templates');
app.set('view engine', 'liquid');

app.use(express.json());
app.use(express.static(path.join(__dirname,'public')));

require('./routes/routes')(router);
app.use('/', router);

app.listen(port);

Api.fetchEffects();
Api.fetchPalettes();
Api.fetchStatus();

console.log(`App Runs on ${port}`);