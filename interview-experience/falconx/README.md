# FalconX's assignment

## Problem Statement: 
    Propose a design for a market data feed handler.   

## Project Description

### Introduction
    This project is a design document for a Market-Data Feed Handler, to be used with a Trading Platform. A market-data feed handler is a software component that receives real-time market data from exchanges or other data providers, processes it, and distributes it to downstream systems such as trading algorithms, smart order-routers or user interfaces.

### Design
    Feed Handler consists of a market data consumer process which publishes data over a publish-subscribe module( eg. RabbitMQ) to be shared among the services.  

#### Brief:
    Feed Handler uses a microservices architecture to validate, parse & aggregate market data.

#### Components:
   The Application has the following (primary) components:
   - Market Data Consumer : Component connects to the external market data source stream.
   - A pub-sub module (rabbitmq|redis pubsub)for data sharing among various services.
   - Stock Tracker Service writes it to a time series database
   - Slow Feed Data Service
   - Order book creator service
   - Fast Feed API
   - Slow Feed API
