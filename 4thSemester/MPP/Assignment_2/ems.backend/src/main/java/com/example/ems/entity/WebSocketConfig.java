package com.example.ems.entity;
import org.springframework.context.annotation.Configuration;
import org.springframework.messaging.simp.config.MessageBrokerRegistry;
import org.springframework.web.socket.config.annotation.EnableWebSocketMessageBroker;
import org.springframework.web.socket.config.annotation.StompEndpointRegistry;
import org.springframework.web.socket.config.annotation.WebSocketMessageBrokerConfigurer;

@Configuration
@EnableWebSocketMessageBroker
public class WebSocketConfig implements WebSocketMessageBrokerConfigurer {

    @Override
    public void configureMessageBroker(MessageBrokerRegistry config) {
        // Enable a simple in-memory message broker to route messages between clients and server endpoints
        config.enableSimpleBroker("/topic"); // Define the topic prefix for broadcasting messages
        config.setApplicationDestinationPrefixes("/app"); // Define the prefix for messages to be routed to server endpoints
    }

    @Override
    public void registerStompEndpoints(StompEndpointRegistry registry) {
        // Register a WebSocket endpoint for clients to connect to
        registry.addEndpoint("/websocket").withSockJS(); // SockJS fallback for browsers that do not support WebSocket
    }
}
